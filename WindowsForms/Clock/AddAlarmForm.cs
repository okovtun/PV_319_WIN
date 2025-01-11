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
		public Alarm Alarm { get; set; }
		OpenFileDialog open = null;
		public AddAlarmForm()
		{
			InitializeComponent();
			dtpDate.Enabled = false;
			Alarm = new Alarm();
			open = new OpenFileDialog();
			open.Filter = "All sound files (*.mp3,*.wav, *flac)|*mp3;*.wav;*.flac|MP-3 (*.mp3)|*.mp3|WAV (*.wav)|*.wav|Flac (*.flac)|*.flac";
		}

		private void cbUseDate_CheckedChanged(object sender, EventArgs e)
		{
			dtpDate.Enabled = cbUseDate.Checked;
		}
		void SetWeekDays(bool[] week)
		{
			for (int i = 0; i < clbWeekDays.Items.Count; i++)
			{
				clbWeekDays.SetItemChecked(i, week[i]);
			}
		}
		private void btnOK_Click(object sender, EventArgs e)
		{
			this.DialogResult = DialogResult.OK;
			Week week = new Week
				(
					clbWeekDays.
					Items.
					Cast<object>().
					Select((item, index) => clbWeekDays.GetItemChecked(index)).ToArray()
				);
			Console.WriteLine(week);
			Alarm.Date = dtpDate.Enabled ? dtpDate.Value : DateTime.MinValue;
			Alarm.Time = dtpTime.Value.TimeOfDay;
			Alarm.Weekdays = week;
			Alarm.Filename = lblAlarmFile.Text;
			Alarm.Message = rtbMessage.Text;
			if (Alarm.Filename == "" || Alarm.Filename == "File:")
			{
				this.DialogResult = DialogResult.None;
				MessageBox.Show
					(
						this, 
						"Выберите звуковой файл", 
						"Warning", 
						MessageBoxButtons.OK, 
						MessageBoxIcon.Warning
					);
			}
		}

		private void btnFile_Click(object sender, EventArgs e)
		{
			if (open.ShowDialog() == DialogResult.OK)
			{
				lblAlarmFile.Text = open.FileName;
			}
		}

		private void AddAlarmForm_Load(object sender, EventArgs e)
		{
			if (Alarm.Date != DateTime.MinValue)
			{
				cbUseDate.Checked = true;
				dtpDate.Value = Alarm.Date;
			}
			dtpTime.Value = DateTime.Now.Date + Alarm.Time;
			SetWeekDays(Alarm.Weekdays.ExtractWeekDays());
			lblAlarmFile.Text = Alarm.Filename;
			rtbMessage.Text = Alarm.Message;
		}
	}
}
