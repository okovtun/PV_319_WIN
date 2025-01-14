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
	public partial class AlarmsForm : Form
	{
		AddAlarmForm addAlarm = null;
		OpenFileDialog openFile = null;
		public ListBox LB_Alarms
		{
			get => lbAlarms;
			//get
			//{
			//	return lbAlarms;
			//}
		}
		public AlarmsForm()
		{
			InitializeComponent();
			addAlarm = new AddAlarmForm();
			openFile = new OpenFileDialog();
		}

		private void btnAdd_Click(object sender, EventArgs e)
		{
			addAlarm.StartPosition = FormStartPosition.Manual;
			addAlarm.Location = new Point(this.Location.X + 25, this.Location.Y + 25);
			DialogResult result = addAlarm.ShowDialog();
			if (result == DialogResult.OK)
			{
				lbAlarms.Items.Add(new Alarm(addAlarm.Alarm));  //CopyConstructor
			}
		}

		private void lbAlarms_DoubleClick(object sender, EventArgs e)
		{
			if (lbAlarms.Items.Count > 0)
			{
				if (lbAlarms.SelectedItem != null)
				{
					addAlarm.Alarm = lbAlarms.SelectedItem as Alarm;
					addAlarm.Location = new Point(this.Location.X + 25, this.Location.Y + 25);
					if (addAlarm.ShowDialog() == DialogResult.OK)
					{
						//lbAlarms.SelectedItem = new Alarm(addAlarm.Alarm);
						lbAlarms.Items[lbAlarms.SelectedIndex] = addAlarm.Alarm;
					}
				}
				else
					MessageBox.Show(this, "Выберите будильник", "Info", MessageBoxButtons.OK, MessageBoxIcon.Information);
			}
			else btnAdd_Click(sender, e);
		}

		private void btnDelete_Click(object sender, EventArgs e)
		{
			lbAlarms.Items.Remove(lbAlarms.SelectedItem);
		}

		private void lbAlarms_KeyDown(object sender, KeyEventArgs e)
		{
			if (e.KeyCode == Keys.Delete) btnDelete_Click(sender, e);
		}
	}
}
