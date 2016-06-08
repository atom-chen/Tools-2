package dk.cego.spritemapper;

import java.awt.Dimension;
import java.io.IOException;
import java.io.OutputStream;
import java.io.OutputStreamWriter;
import java.nio.charset.Charset;
import java.util.List;

public class JsonMetaStream implements SpriteMapperMetaStream {

    @Override
    public void write(List<Sprite> sprites, OutputStream out) throws IOException {
        Charset c = Charset.defaultCharset();
        OutputStreamWriter o = new OutputStreamWriter(out, c);
        int i = 1;
        
        o.write("{\"frames\":{\n");

        for (Sprite s : sprites) {
            Dimension d = new Dimension(s.w, s.h);
            if (s.rotated) {
                d.width = s.h;
                d.height = s.w;
            }
            
            o.write("  \"" + s.name + "\":{\n");
            o.write("    \"frame\":{\n");
            o.write("      \"w\":" + d.width + ",\n");
            o.write("      \"h\":" + d.height + ",\n");
            o.write("      \"x\":" + s.x + ",\n");
            o.write("      \"y\":" + s.y + "\n");
            o.write("    },\n");
            o.write("    \"spriteSourceSize\":{\n");
            o.write("      \"x\":" + s.colorRect.x + ",\n");
            o.write("      \"y\":" + s.colorRect.y + "\n");
            o.write("    },\n");
            o.write("    \"sourceSize\":{\n");
            o.write("      \"w\":" + s.originalDimension.width + ",\n");
            o.write("      \"h\":" + s.originalDimension.height + "\n");
            o.write("    },\n");
            o.write("    \"rotated\":" + s.rotated + "\n");
            o.write("  }\n");

            if(i != sprites.size()) {
                o.write("  ,\n");
            }
            i++;
        }

        o.write("}}");
        o.flush();
    }

}
