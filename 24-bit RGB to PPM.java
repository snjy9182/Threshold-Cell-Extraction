// 24-bit RGB to PPM.java
// (Relies upon a 24-bit RGB color output of a segmented DIC image)
// (Referenced from Johannes Schindelin's PNM_Writer.java)
//
// Wu Lab, Johns Hopkins University
//
// Author: Sun Jay Yoo
// Date: June 15, 2017

import ij.*;
import ij.process.*;
import ij.gui.*;
import java.awt.*;
import ij.plugin.*;
import ij.io.SaveDialog;
import java.io.*;
import java.util.*;
import java.util.regex.*;
import java.awt.image.*;

public class PNM_Writer implements PlugIn {

	public void run(String arg) {
		ImagePlus img=IJ.getImage();
		if (img.getStackSize() != 1) {
			IJ.error("Error Code 1: can only save 2D images.");
			return;
		}
		boolean isGray = false;
		String extension = null;
		if (img.getBitDepth() == 8) {
			isGray = true;
			extension = ".pgm";
		} else if (img.getBitDepth()==24)
			extension = ".ppm";
		else {
			IJ.error("Error Code 2: can only save 8-bit and 24-bit RGB images.");
			return;
		}
		String title=img.getTitle();
		int length=title.length();
		for(int i=2;i<5;i++)
			if(length>i+1 && title.charAt(length-i)=='.') {
				title=title.substring(0,length-i);
				break;
			}

		SaveDialog od = new SaveDialog("PPM Writer", title, extension);
		String dir=od.getDirectory();
		String name=od.getFileName();

		if(name==null)
			return;
		try {
			IJ.showStatus("Writing PPM "+dir+name+"...");
			OutputStream fileOutput =
				new FileOutputStream(dir + name);
			DataOutputStream output =
				new DataOutputStream(fileOutput);

			int w = img.getWidth(), h = img.getHeight();
			output.writeBytes((isGray ? "P5" : "P6")
					+ "\n# Written by ImageJ PPM Writer\n"
					+ w + " " + h + "\n255\n");
			if (isGray)
				output.write(
					(byte[])img.getProcessor().getPixels(),
					0, w * h);
			else {
				byte[] pixels = new byte[w * h * 3];
				ColorProcessor proc =
					(ColorProcessor)img.getProcessor();
				for (int j = 0; j < h; j++)
					for (int i = 0; i < w; i++) {
						int c = proc.getPixel(i, j);
						pixels[3 * (i + w * j) + 0] =
							(byte)((c & 0xff0000) >> 16);
						pixels[3 * (i + w * j) + 1] =
							(byte)((c & 0xff00) >> 8);
						pixels[3 * (i + w * j) + 2] =
							(byte)(c & 0xff);
					}
				output.write(pixels, 0, pixels.length);
			}
			output.flush();
		} catch(IOException e) {
			e.printStackTrace();
			IJ.error("Error Code 3: error writing file.");
		}
		IJ.showStatus("");
	}

};

