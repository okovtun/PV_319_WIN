using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Clock
{
	public partial class AddAlarmForm : Form
	{
		public AddAlarmForm()
		{
			InitializeComponent();
			dtpDate.Enabled = false;
		}

		private void cbUseDate_CheckedChanged(object sender, EventArgs e)
		{
			dtpDate.Enabled = cbUseDate.Checked;
		}

		private void btnOK_Click(object sender, EventArgs e)
		{
			for (int i = 0; i < clbWeekDays.Items.Count; i++)
			{
				Console.Write(clbWeekDays.GetItemChecked(i) + "\t");
			}
			Console.WriteLine();
		}
	}
}
