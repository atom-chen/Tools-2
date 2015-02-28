using System;
using Gtk;

namespace FileArchiveToolTest
{
	public partial class MainWindow: Gtk.Window
	{
		public MainWindow () : base (Gtk.WindowType.Toplevel)
		{
			Build ();

			ArchiveData pArchiveData = new ArchiveData ();
			UnArchiveParam pUnArchiveParam = new UnArchiveParam ();
			string path = "E:\\新建文件夹.abc";
			pUnArchiveParam.setUnArchiveFilePath (path);
			pUnArchiveParam.setUnArchiveOutDir (Util.getFullPathNoFileName (path));
			pArchiveData.unArchiveFile (pUnArchiveParam);
		}

		protected void OnDeleteEvent (object sender, DeleteEventArgs a)
		{
			Application.Quit ();
			a.RetVal = true;
		}
	}
}