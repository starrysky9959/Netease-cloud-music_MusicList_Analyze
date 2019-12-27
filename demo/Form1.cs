using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;
using System.Text.RegularExpressions;

namespace demo
{
    
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            init();            
        }
        private void init()
        {
            StreamReader inFile = new StreamReader(IGNORE_PATH, Encoding.Default);
            string line;
            while ((line = inFile.ReadLine()) != null)
            {
                ignoreList.Add(line);
                ignoreListBox.Items.Add(line);
            }
            inFile.Close();
        }

        //文件路径，按需修改
        static string EXE_PATH = @".\test.exe";
        static string MUSIC_INPUT_PATH = @".\assert\output\music_output.txt";
        static string WORD_INPUT_PATH = @".\assert\output\word_output.txt";
        static string IGNORE_PATH = @".\assert\lyrics\ignore.txt";
        static string INFO_PATH = @".\assert\output\info_output.txt";
        static string UTF8_PATH = @".\assert\output\utf8.txt";

        string targetWord;
        Int32 wordSize;
        Int32 targetFrequency;
        List<HotWord> myList = new List<HotWord>();
        List<string> ignoreList = new List<string>();

        public void update()
        {
            musicListView.Items.Clear();
            wordListView.Items.Clear();
            targetWord = target.Text;
            System.Diagnostics.Process myexe = new System.Diagnostics.Process();
            myexe.StartInfo.FileName = EXE_PATH;
            myexe.StartInfo.Arguments = targetWord;
            myexe.StartInfo.UseShellExecute = false;
            myexe.StartInfo.CreateNoWindow = true;
            myexe.Start();
            //等待外部程序退出后才能往下执行
            myexe.WaitForExit();
            //MessageBox.Show("分析完毕");

            //读取曲目内容
            StreamReader inFile = new StreamReader(MUSIC_INPUT_PATH, Encoding.Default);
            string line;
            while ((line = inFile.ReadLine()) != null)
            {
                if (line.Length <= 1)
                    continue;
                ListViewItem item = new ListViewItem();
                item.Text = line;
                musicListView.Items.Add(item);
            }
            inFile.Close();
            //读取单词信息
            inFile = new StreamReader(WORD_INPUT_PATH, Encoding.Default);
            ////指定单词词频
            //line = inFile.ReadLine();
            //targetFrequency = Convert.ToInt32(line);
            //label1.Text = line;
            //单词总数
            //line = inFile.ReadLine();
            //wordSize = Convert.ToInt32(line);
            while ((line = inFile.ReadLine()) != null)
            {
                if (Regex.IsMatch(line, "^[0-9]*$"))
                {
                    //添加频率
                    HotWord temp = new HotWord();
                    temp.frequency = Convert.ToInt32(line);
                    ListViewItem item = new ListViewItem();
                    item.SubItems.Add(Convert.ToInt32(line).ToString());
                    //读取单词
                    line = inFile.ReadLine();
                    temp.word = line;
                    myList.Add(temp);
                    item.Text = line;
                    wordListView.Items.Add(item);
                }
                else
                {
                    myList[myList.Count - 1].music.Add(line);
                }
            }
            inFile.Close();

            AnsiToUtf8();
        }
        private void AnsiToUtf8()
        {

            //Ansi格式的文件路径
            //FileStream fs = new FileStream(INFO_PATH, FileMode.Open, FileAccess.Read);
            StreamReader sr = new StreamReader(INFO_PATH, Encoding.Default);

            //另存的文件路径            
            //FileStream fsw = new FileStream(UTF8_PATH, FileMode.Create, FileAccess.Write);

            //另存为UTF-8
            StreamWriter sw = new StreamWriter(UTF8_PATH, false,Encoding.UTF8);

            //char[] charArr = new char[20];
            //int count = sr.Read(charArr, 0, 20);            
            //while (count != 0)
            //{
            //    sw.Write(charArr, 0, 20);               
            //    count = sr.Read(charArr, 0, 20);
            //}
            string line;
            while ((line = sr.ReadLine()) != null)
            {
                sw.WriteLine(line);
                MessageBox.Show(line);
            }
            sw.Close();
            sr.Close();
        }

        private void start_Click(object sender, EventArgs e)
        {
            update();
        }

        private void target_TextChanged(object sender, EventArgs e)
        {
            targetWord = target.Text;
        }

        private void searchButton_Click(object sender, EventArgs e)
        {
            targetWord = target.Text;
            containsListView.Items.Clear();
            label1.Text = "0";
            foreach (HotWord i in myList)
                if (i.word.Equals(targetWord))
                {
                    foreach (string str in i.music)
                    {
                        ListViewItem item = new ListViewItem();
                        item.Text = str;
                        containsListView.Items.Add(item);
                    }
                    label1.Text = i.frequency.ToString();
                    break;
                }            
        }

        private void addIgnoreButton_Click(object sender, EventArgs e)
        {            
            ignoreList.Add(ignoreWordTextBox.Text);
            ignoreListBox.Items.Add(ignoreWordTextBox.Text);
            StreamWriter outFile = new StreamWriter(IGNORE_PATH, false, Encoding.Default);
            foreach (string item in ignoreListBox.Items)
            {
                outFile.WriteLine(item);
            }
            outFile.Close();
            update();
        }

        private void deleteIgnoreButton_Click(object sender, EventArgs e)
        {
            Int32 count = ignoreListBox.SelectedItems.Count;
            List<string> selectedItems = new List<string>();
            if (count != 0)
            {
                for (int i = 0; i < count; ++i)
                {
                    selectedItems.Add(ignoreListBox.SelectedItems[i].ToString());
                }
                foreach(string item in selectedItems)
                {
                    ignoreListBox.Items.Remove(item);
                    ignoreList.Remove(item);
                }
            }
            StreamWriter outFile = new StreamWriter(IGNORE_PATH, false, Encoding.Default);
            foreach (string item in ignoreListBox.Items)
            {
                outFile.WriteLine(item);
            }
            outFile.Close();
            update();
        }
    }

    public class HotWord
    {
        public string word;
        public Int32 frequency;
        public List<string> music = new List<string>();
    }
}
