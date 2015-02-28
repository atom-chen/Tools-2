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
			pUnArchiveParam.setUnArchiveFilePath ();
		}

		protected void OnDeleteEvent (object sender, DeleteEventArgs a)
		{
			Application.Quit ();
			a.RetVal = true;
		}
	}
}