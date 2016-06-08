/**
 * Copyright (C) 2011 CEGO ApS
 * Written by Robert Larsen <robert@komogvind.dk> for CEGO ApS
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
package dk.cego.spritemapper;

import java.awt.Dimension;
import java.awt.Graphics2D;
import java.awt.image.BufferedImage;
import java.awt.Color;
import java.io.*;
import java.util.*;

import javax.imageio.ImageIO;

import org.apache.tools.ant.*;
import org.apache.tools.ant.types.FileSet;

import dk.cego.spritemapper.spritecomparators.AreaComparator;
import dk.cego.spritemapper.spritehandlers.Landscape;

public class SpriteMapperTask extends Task {
    private List<FileSet> fileSets;
    private List<LayoutMeta> meta;
    private File destFile;
    private String theme;
    private String prefix;
    private int maxWidth;
    private boolean drawFrames;
    private boolean trim;
    private boolean ieLoadTestPixel;

    public SpriteMapperTask() {
        fileSets = new LinkedList<FileSet>();
        meta = new LinkedList<LayoutMeta>();
        destFile = null;
        theme = "";
        prefix = "";
        drawFrames = false;
        trim = true;
        ieLoadTestPixel = false;
    }

    public LayoutMeta createLayoutMeta() {
        LayoutMeta m = new LayoutMeta();
        meta.add(m);
        return m;
    }

    public void setIELoadTestPixel(boolean ieLoadTestPixel) {
        this.ieLoadTestPixel = ieLoadTestPixel;
    }

    public void setTrim(boolean trim) {
        this.trim = trim;
    }

    public void setDrawframes(boolean draw) {
        this.drawFrames = draw;
    }

    public void setMaxwidth(int maxWidth) {
        this.maxWidth = maxWidth;
    }

    public void setDestfile(File f) {
        this.destFile = f;
    }

    public void setTheme(String t) {
        this.theme = t;
    }
    
    public void setPrefix(String p) {
        this.prefix = p;
    }
    
    public void addFileset(FileSet files) {
        fileSets.add(files);
    }

    @Override
    public void execute() {
        if (destFile == null) {
            throw new BuildException("'destfile' must be set.");
        }

        try {
            // Find files and instantiate sprites
            CombinedFileSizeFileHandler combinedSize = new CombinedFileSizeFileHandler();
            SpriteImporter importer = new SpriteImporter().setFileHandler(combinedSize);
            List<Sprite> sprites = new ArrayList<Sprite>();
            for (FileSet fs : fileSets) {
                DirectoryScanner ds = fs.getDirectoryScanner();
                for (String path : ds.getIncludedFiles()) {
                    sprites.add(importer.importSprite(ds.getBasedir(), path));
                }
            }

            // Write out resulting file
            // SpriteLayouter layouter = new dk.cego.spritemapper.maxrects.OptimalMaxRectsLayouter();
            SpriteLayouter layouter = new OptimalAlgorithmLayouter();
            SpriteMapper mapper = new SpriteMapper(sprites).setTrim(trim).setSpritePreHandler(new Landscape())
                    .setSpriteSorter(new AreaComparator()).setLayouter(layouter).doLayout(maxWidth);

            for (LayoutMeta m : meta) {
                m.execute(mapper);
            }
            String fileFormat = fileExtension(destFile);
            Dimension resultSize = mapper.getLayoutDimension();
            if (ieLoadTestPixel) {
                if (resultSize.width > resultSize.height) {
                    resultSize.width++;
                } else {
                    resultSize.height++;
                }
            }
            BufferedImage result = getImageForFormat(fileFormat, resultSize);
            Graphics2D graphics = (Graphics2D) result.getGraphics();
            mapper.paint(graphics, drawFrames);

            if (ieLoadTestPixel) {
                graphics.setPaint(Color.BLUE);
                graphics.fillRect(result.getWidth() - 1, result.getHeight() - 1, 1, 1);
            }

            ImageIO.write(result, fileFormat, destFile);

            System.out.println("Layouter used: " + layouter);
            System.out.println("Resulting file is " + result.getWidth() + " by " + result.getHeight() + " pixels. Area is "
                    + (result.getWidth() * result.getHeight()) + " square pixels.");
            System.out.println("Waste: "
                    + (int) (100.0 - 100.0 * (double) Sprite.collectiveArea(sprites) / (double) (result.getWidth() * result.getHeight()))
                    + "%");
            System.out.println("Combined filesize: " + combinedSize.size + " Map filesize: " + destFile.length());
        } catch (IOException ioe) {
            throw new BuildException("Could not generate spritemapper: " + ioe);
        }
    }

    private final static BufferedImage getImageForFormat(String format, Dimension size) {
        return new BufferedImage(size.width, size.height,
                (format.equalsIgnoreCase("jpg") || format.equalsIgnoreCase("jpeg")) ? BufferedImage.TYPE_INT_RGB
                        : BufferedImage.TYPE_INT_ARGB);
    }

    public String getPrefix(){
        if(!this.prefix.equals("")){
            return prefix;
        } else {
            return GssMetaStream.DEFAULT_PREFIX;
        }
    }
    
    private final static String fileExtension(File f) {
        String name = f.getName();
        int idx = name.lastIndexOf(".");
        return name.substring(idx + 1);
    }

    public class LayoutMeta {
        private File destFile = null;
        private String format = "zwoptex2";

        public void setDestfile(File f) {
            this.destFile = f;
        }

        public void setFormat(String f) {
            this.format = f;
        }
        
        public void execute(SpriteMapper mapper) throws IOException {
            if (destFile == null) {
                throw new BuildException("'meta' tag needs a 'destfile' attribute.");
            }

            mapper.setMetaStreamer(getStreamer(mapper)).doMetaStream(new FileOutputStream(destFile));
        }

        private SpriteMapperMetaStream getStreamer(SpriteMapper mapper) {
            if (format.equals("zwoptex2")) {
                return new Zwoptex2MetaStream(SpriteMapperTask.this.destFile.getName(), mapper.getLayoutDimension());
            }
            if (format.equals("gss")) {
                return new GssMetaStream(SpriteMapperTask.this.getPrefix(), SpriteMapperTask.this.destFile.getName(), SpriteMapperTask.this.theme, null);
            }
            if (format.equals("json")) {
                return new JsonMetaStream();
            }

            throw new BuildException("Unknown format '" + format + "'");
        }
        
    }

    private static class CombinedFileSizeFileHandler implements ObjectHandler<File> {
        public long size = 0l;

        public void handle(File f) {
            size += f.length();
        }
    }
}
