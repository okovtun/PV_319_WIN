using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Clock
{
	public class Week
	{
		public static readonly string[] Weekdays = new string[]{"Пн","Вт","Ср","Чт","Пт","Сб","Вс"};
		byte week;
		public Week()
		{
			week = 0;
		}
		public Week(bool[] days)
		{
			CompressWeekDays(days);
		}
		//public void SetDay(int day)
		//{
		//	if (day > 6) return;
		//	week |= (byte)(1 << day);
		//}
		public void CompressWeekDays(bool[] days)
		{
			for (byte i = 0; i < days.Length; i++)
			{
				//byte day = 1;
				if (days[i]) week |= (byte)(1 << i);
				//if (days[i]) SetDay(i);
			}
		}
		public bool[] ExtractWeekDays()
		{
			bool[] weekDays = new bool[7];
			for (byte i = 0; i < 7; i++)
			{
				weekDays[i] = (week & (byte)(1 << i)) != 0;
			}
			return weekDays;
		}
		public override string ToString()
		{
			string weekdays = "";
			for (byte i = 0; i < Weekdays.Length; i++)
			{
				if (((1 << i) & week) != 0)
					weekdays += $"{Weekdays[i]},";
			}
			return weekdays;
		}
	}
}
