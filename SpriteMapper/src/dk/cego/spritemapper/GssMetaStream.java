/**
 * Copyright (C) 2011 CEGO ApS
 * Written by Kristian Varmark <kristian@komogvind.dk> for CEGO ApS
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

import java.io.ByteArrayOutputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStream;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.nio.charset.Charset;
import java.util.List;

public class GssMetaStream implements SpriteMapperMetaStream {

    public static final String DEFAULT_PREFIX = "./media/graphics/maps/";
    private String prefix;
    private String filename;
    private String theme;
    private String testPage;

    public GssMetaStream(String prefix, String filename, String theme, String testPage) {
        this.prefix = prefix;
        this.filename = filename;
        this.theme = theme;
        this.testPage = testPage;
    }
    
    public String getTheme(){
        if(!theme.equals("")){
            return theme + "_";
        } else {
            return "";
        }
    }

    public void writeTestPage(List<Sprite> sprites) throws IOException {
        Charset c = Charset.defaultCharset();
        OutputStreamWriter o = new OutputStreamWriter(new FileOutputStream(testPage), c);
        o.write("<!DOCTYPE html>\n<html>\n\t<head>\n\t<style>\n");

        ByteArrayOutputStream outputStream = new ByteArrayOutputStream();
        PrintWriter html = new PrintWriter(outputStream);

        for (Sprite s : sprites) {

            String name = filename.substring(0, (filename.indexOf("."))) + "_"
                    + s.name.replace('\\', '_').replace('/', '_').substring(0, s.name.indexOf("."));
            // Define padding
            int paddingTop, paddingLeft, paddingBottom, paddingRight;

            if (!s.rotated) {
                paddingTop = s.colorRect.y;
                paddingRight = s.originalDimension.width - s.colorRect.w - s.colorRect.x;
                paddingBottom = s.originalDimension.height - s.colorRect.h - s.colorRect.y;
                paddingLeft = s.colorRect.x;
            } else {
                paddingTop = s.colorRect.x;
                paddingRight = s.colorRect.y;
                paddingBottom = s.originalDimension.width - s.colorRect.w - s.colorRect.x;
                paddingLeft = s.originalDimension.height - s.colorRect.h - s.colorRect.y;
            }

            // Define inner div mixin

            String styleName = "spritemap_" + getTheme() + name + "";

            if (styleName.equals("spritemap_out_toolsmenu_arrow")) {
                System.out.println(s.x + ", " + s.y);
                System.out.println(s.colorRect.toString());
            }

            o.write("\t." + styleName + " {\n");
            o.write("\t\tbackground:url('" + prefix + filename + "')");

            if (s.x > 0 || s.y > 0) {
                o.write(String.format(" -%dpx -%dpx", s.x, s.y));
            }

            o.write(";\n");
            o.write("\t\twidth:" + s.w + "px;\n");
            o.write("\t\theight:" + s.h + "px;\n");
            o.write("\tbackground-clip: content-box;\n");
            o.write("\tbackground-origin: content-box;\n");

            if (s.rotated) {
                int tx = 0;
                int ty = s.originalDimension.height;
                String transform = String.format("translate(%dpx,%dpx) rotate(-90deg);\n", tx, ty);

                o.write("\t\ttransform:" + transform);
                o.write("\t\t-ms-transform:" + transform);
                o.write("\t\t-moz-transform:" + transform);
                o.write("\t\t-webkit-transform:" + transform);
                o.write("\t\t-o-transform:" + transform);

                o.write("\t\ttransform-origin:0% 0%;\n");
                o.write("\t\t-ms-transform-origin:0% 0%;\n");
                o.write("\t\t-moz-transform-origin:0% 0%;\n");
                o.write("\t\t-webkit-transform-origin:0% 0%;\n");
                o.write("\t\t-o-transform-origin:0% 0%;\n");
            } else {
                o.write("\t\ttransform: none;\n");
                o.write("\t\t-ms-transform: none;\n");
                o.write("\t\t-moz-transform: none;\n");
                o.write("\t\t-webkit-transform: none;\n");
                o.write("\t\t-o-transform: none;\n");
            }

            if (paddingTop != 0 || paddingRight != 0 || paddingBottom != 0 || paddingLeft != 0) {
                o.write(String.format("\t\tpadding: %dpx %dpx %dpx %dpx;\n", paddingTop, paddingRight, paddingBottom, paddingLeft));
            }

            o.write("\t}\n\n");

            html.println(String.format("<div style=\"display: inline-block; width: %dpx; height: %dpx\"><div class=\"%s\"></div></div>",
                    s.originalDimension.width, s.originalDimension.height, styleName));
        }

        html.close();

        o.write("\t</style>\n");
        o.write("</head>\n<body style=\"margin: 0px\">\n");
        o.write(outputStream.toString("utf-8"));
        o.write("</body>\n</html>\n");

        o.flush();
    }

    @Override
    public void write(List<Sprite> sprites, OutputStream out) throws IOException {
        Charset c = Charset.defaultCharset();
        OutputStreamWriter o = new OutputStreamWriter(out, c);

        if (testPage != null) {
            writeTestPage(sprites);
        }

        String basename = filename.substring(0, (filename.indexOf("."))) + "_";

        for (Sprite s : sprites) {
            String name = basename + s.name.replace('\\', '_').replace('/', '_').substring(0, s.name.indexOf("."));

            // Define padding
            int paddingTop, paddingLeft, paddingBottom, paddingRight;
            
            if (!s.rotated) {
                paddingTop = s.colorRect.y;
                paddingRight = s.originalDimension.width - s.colorRect.w - s.colorRect.x;
                paddingBottom = s.originalDimension.height - s.colorRect.h - s.colorRect.y;
                paddingLeft = s.colorRect.x;
            } else {
                paddingTop = s.colorRect.x;
                paddingRight = s.colorRect.y;
                paddingBottom = s.originalDimension.width - s.colorRect.w - s.colorRect.x;
                paddingLeft = s.originalDimension.height - s.colorRect.h - s.colorRect.y;
            }

            // Define inner div mixin

            String mixinFunctionName = "spritemap_mixin_" + getTheme() + name + "()";

            o.write("@defmixin " + mixinFunctionName + " {\n");
            o.write("\tbackground:url('" + prefix + filename + "')");

            if (s.x > 0 || s.y > 0) {
                o.write(String.format(" -%dpx -%dpx", s.x, s.y));
            }

            o.write(";\n");
            o.write("\twidth:" + s.w + "px;\n");
            o.write("\theight:" + s.h + "px;\n");
            o.write("\tbackground-clip: content-box;\n");
            o.write("\tbackground-origin: content-box;\n");

            if (s.rotated) {
                int tx = 0;
                int ty = s.originalDimension.height;
                String transform = String.format("translate(%dpx,%dpx) rotate(-90deg);\n", tx, ty);

                o.write("\ttransform:" + transform);
                o.write("\t-ms-transform:" + transform);
                o.write("\t-moz-transform:" + transform);
                o.write("\t-webkit-transform:" + transform);
                o.write("\t-o-transform:" + transform);

                o.write("\ttransform-origin:0% 0%;\n");
                o.write("\t-ms-transform-origin:0% 0%;\n");
                o.write("\t-moz-transform-origin:0% 0%;\n");
                o.write("\t-webkit-transform-origin:0% 0%;\n");
                o.write("\t-o-transform-origin:0% 0%;\n");
            } else {
                o.write("\ttransform: none;\n");
                o.write("\t-ms-transform: none;\n");
                o.write("\t-moz-transform: none;\n");
                o.write("\t-webkit-transform: none;\n");
                o.write("\t-o-transform: none;\n");
            }

            if (paddingTop != 0 || paddingRight != 0 || paddingBottom != 0 || paddingLeft != 0) {
                o.write(String.format("\tpadding: %dpx %dpx %dpx %dpx;\n", paddingTop, paddingRight, paddingBottom, paddingLeft));
            }

            o.write("}\n");

            // Define style which uses mixin

            o.write(".spritemap_" + getTheme() + name + " {\n");
            o.write("\t@mixin ");
            o.write(mixinFunctionName);
            o.write(";\n");
            o.write("}\n");

            // Define size mixin

            String sizeMixinFunctionName = "spritemap_mixin_" + getTheme() + name + "_size()";
            o.write("@defmixin " + sizeMixinFunctionName + " {\n");
            o.write("\twidth:" + s.originalDimension.width + "px;\n");
            o.write("\theight:" + s.originalDimension.height + "px;\n");
            o.write("}\n");

            // Define size style

            o.write(".spritemap_" + getTheme() + name + "_size {\n");
            o.write("\t@mixin ");
            o.write(sizeMixinFunctionName);
            o.write(";\n");
            o.write("}\n\n");
            
            // Define width and height variables

            String widthVariableName = ("spritemap_mixin_" + getTheme() + name + "_width").toUpperCase();
            String heightVariableName = ("spritemap_mixin_" + getTheme() + name + "_height").toUpperCase();

            o.write("@def " + widthVariableName + " " + s.originalDimension.width + "px;\n");
            o.write("@def " + heightVariableName + " " + s.originalDimension.height + "px;\n");
            o.write("\n");
        }
        o.flush();
    }
}