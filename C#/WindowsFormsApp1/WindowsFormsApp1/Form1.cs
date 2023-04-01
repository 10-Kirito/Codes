using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsFormsApp1
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }
        
        // 计算按钮的功能设计
        private void button1_Click(object sender, EventArgs e)
        {
            int birthYear, birthMonth, birthDay;
            DateTime now = DateTime.Now;
            birthYear = Int32.Parse(year.Text);
            birthMonth = Int32.Parse(month.Text);
            birthDay = Int32.Parse(day.Text);

            if ((now.Month > birthMonth) || ((now.Month == birthMonth) && (now.Day >= birthDay)))
                result.Text = (now.Year - birthYear).ToString();
            else
                result.Text = (now.Year - birthYear - 1).ToString();
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void tableLayoutPanel1_Paint(object sender, PaintEventArgs e)
        {

        }

        // 输入的年
        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }

        // 输入的月
        private void textBox2_TextChanged(object sender, EventArgs e)
        {

        }

        // 输入的日
        private void textBox3_TextChanged(object sender, EventArgs e)
        {

        }


        private void textBox4_TextChanged(object sender, EventArgs e)
        {

        }
    }
}
