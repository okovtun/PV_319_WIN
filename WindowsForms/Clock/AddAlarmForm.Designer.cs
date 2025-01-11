namespace Clock
{
	partial class AddAlarmForm
	{
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.IContainer components = null;

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		/// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
		protected override void Dispose(bool disposing)
		{
			if (disposing && (components != null))
			{
				components.Dispose();
			}
			base.Dispose(disposing);
		}

		#region Windows Form Designer generated code

		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
			this.cbUseDate = new System.Windows.Forms.CheckBox();
			this.dtpDate = new System.Windows.Forms.DateTimePicker();
			this.dtpTime = new System.Windows.Forms.DateTimePicker();
			this.lblAlarmFile = new System.Windows.Forms.Label();
			this.btnOK = new System.Windows.Forms.Button();
			this.btnCancel = new System.Windows.Forms.Button();
			this.btnFile = new System.Windows.Forms.Button();
			this.clbWeekDays = new System.Windows.Forms.CheckedListBox();
			this.rtbMessage = new System.Windows.Forms.RichTextBox();
			this.lblMessage = new System.Windows.Forms.Label();
			this.SuspendLayout();
			// 
			// cbUseDate
			// 
			this.cbUseDate.AutoSize = true;
			this.cbUseDate.Font = new System.Drawing.Font("Microsoft Sans Serif", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
			this.cbUseDate.Location = new System.Drawing.Point(13, 13);
			this.cbUseDate.Name = "cbUseDate";
			this.cbUseDate.Size = new System.Drawing.Size(117, 29);
			this.cbUseDate.TabIndex = 0;
			this.cbUseDate.Text = "Use date";
			this.cbUseDate.UseVisualStyleBackColor = true;
			this.cbUseDate.CheckedChanged += new System.EventHandler(this.cbUseDate_CheckedChanged);
			// 
			// dtpDate
			// 
			this.dtpDate.CalendarFont = new System.Drawing.Font("Microsoft Sans Serif", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
			this.dtpDate.CustomFormat = "yyyy/MM/dd";
			this.dtpDate.Font = new System.Drawing.Font("Microsoft Sans Serif", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
			this.dtpDate.Format = System.Windows.Forms.DateTimePickerFormat.Custom;
			this.dtpDate.Location = new System.Drawing.Point(13, 49);
			this.dtpDate.Name = "dtpDate";
			this.dtpDate.Size = new System.Drawing.Size(175, 31);
			this.dtpDate.TabIndex = 1;
			// 
			// dtpTime
			// 
			this.dtpTime.CustomFormat = "hh:mm:ss tt";
			this.dtpTime.Font = new System.Drawing.Font("Microsoft Sans Serif", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
			this.dtpTime.Format = System.Windows.Forms.DateTimePickerFormat.Custom;
			this.dtpTime.Location = new System.Drawing.Point(212, 49);
			this.dtpTime.Name = "dtpTime";
			this.dtpTime.ShowUpDown = true;
			this.dtpTime.Size = new System.Drawing.Size(175, 31);
			this.dtpTime.TabIndex = 2;
			// 
			// lblAlarmFile
			// 
			this.lblAlarmFile.AutoSize = true;
			this.lblAlarmFile.Location = new System.Drawing.Point(12, 196);
			this.lblAlarmFile.Name = "lblAlarmFile";
			this.lblAlarmFile.Size = new System.Drawing.Size(26, 13);
			this.lblAlarmFile.TabIndex = 3;
			this.lblAlarmFile.Text = "File:";
			// 
			// btnOK
			// 
			this.btnOK.DialogResult = System.Windows.Forms.DialogResult.OK;
			this.btnOK.Location = new System.Drawing.Point(231, 221);
			this.btnOK.Name = "btnOK";
			this.btnOK.Size = new System.Drawing.Size(75, 23);
			this.btnOK.TabIndex = 4;
			this.btnOK.Text = "OK";
			this.btnOK.UseVisualStyleBackColor = true;
			this.btnOK.Click += new System.EventHandler(this.btnOK_Click);
			// 
			// btnCancel
			// 
			this.btnCancel.DialogResult = System.Windows.Forms.DialogResult.Cancel;
			this.btnCancel.Location = new System.Drawing.Point(312, 221);
			this.btnCancel.Name = "btnCancel";
			this.btnCancel.Size = new System.Drawing.Size(75, 23);
			this.btnCancel.TabIndex = 5;
			this.btnCancel.Text = "Cancel";
			this.btnCancel.UseVisualStyleBackColor = true;
			// 
			// btnFile
			// 
			this.btnFile.Location = new System.Drawing.Point(13, 221);
			this.btnFile.Name = "btnFile";
			this.btnFile.Size = new System.Drawing.Size(75, 23);
			this.btnFile.TabIndex = 6;
			this.btnFile.Text = "Choose file";
			this.btnFile.UseVisualStyleBackColor = true;
			this.btnFile.Click += new System.EventHandler(this.btnFile_Click);
			// 
			// clbWeekDays
			// 
			this.clbWeekDays.CheckOnClick = true;
			this.clbWeekDays.ColumnWidth = 48;
			this.clbWeekDays.FormattingEnabled = true;
			this.clbWeekDays.Items.AddRange(new object[] {
            "Пн",
            "Вт",
            "Ср",
            "Чт",
            "Пт",
            "Сб",
            "Вс"});
			this.clbWeekDays.Location = new System.Drawing.Point(15, 99);
			this.clbWeekDays.MultiColumn = true;
			this.clbWeekDays.Name = "clbWeekDays";
			this.clbWeekDays.Size = new System.Drawing.Size(372, 19);
			this.clbWeekDays.TabIndex = 7;
			// 
			// rtbMessage
			// 
			this.rtbMessage.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
			this.rtbMessage.Location = new System.Drawing.Point(15, 151);
			this.rtbMessage.Name = "rtbMessage";
			this.rtbMessage.Size = new System.Drawing.Size(370, 42);
			this.rtbMessage.TabIndex = 8;
			this.rtbMessage.Text = "";
			// 
			// lblMessage
			// 
			this.lblMessage.AutoSize = true;
			this.lblMessage.Location = new System.Drawing.Point(15, 132);
			this.lblMessage.Name = "lblMessage";
			this.lblMessage.Size = new System.Drawing.Size(112, 13);
			this.lblMessage.TabIndex = 9;
			this.lblMessage.Text = "Введите сообщение:";
			// 
			// AddAlarmForm
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(397, 256);
			this.Controls.Add(this.lblMessage);
			this.Controls.Add(this.rtbMessage);
			this.Controls.Add(this.clbWeekDays);
			this.Controls.Add(this.btnFile);
			this.Controls.Add(this.btnCancel);
			this.Controls.Add(this.btnOK);
			this.Controls.Add(this.lblAlarmFile);
			this.Controls.Add(this.dtpTime);
			this.Controls.Add(this.dtpDate);
			this.Controls.Add(this.cbUseDate);
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
			this.Name = "AddAlarmForm";
			this.Text = "AddAlarm";
			this.Load += new System.EventHandler(this.AddAlarmForm_Load);
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.CheckBox cbUseDate;
		private System.Windows.Forms.DateTimePicker dtpDate;
		private System.Windows.Forms.DateTimePicker dtpTime;
		private System.Windows.Forms.Label lblAlarmFile;
		private System.Windows.Forms.Button btnOK;
		private System.Windows.Forms.Button btnCancel;
		private System.Windows.Forms.Button btnFile;
		private System.Windows.Forms.CheckedListBox clbWeekDays;
		private System.Windows.Forms.RichTextBox rtbMessage;
		private System.Windows.Forms.Label lblMessage;
	}
}