using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Clock
{
	class Alarm
	{
		public DateTime Date { get; set; }
		public DateTime Time { get; set; }
		public Week Weekdays { get; set; }
		public string Filename { get; set; }
		public string Message { get; set; }
		public Alarm()
		{

		}
	}
}
