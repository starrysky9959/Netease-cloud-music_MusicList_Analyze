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
           

        }

        //文件路径，按需修改
        static string EXE_PATH = @".\数据结构层.exe";
        static string MUSIC_INPUT_PATH = @".\assert\output\music_output.txt";
        static string WORD_INPUT_PATH = @".\assert\output\word_output.txt";        
        string targetWord;
        Int32 wordSize;
        Int32 targetFrequency;
        List<HotWord> myList = new List<HotWord>();
        private void start_Click(object sender, EventArgs e)
        {
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
            
            //读取单词信息
            inFile = new StreamReader(WORD_INPUT_PATH, Encoding.Default);
            ////指定单词词频
            //line = inFile.ReadLine();
            //targetFrequency = Convert.ToInt32(line);
            //label1.Text = line;
            //单词总数
            line = inFile.ReadLine();
            wordSize = Convert.ToInt32(line);
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
                    foreach (string str in i.music) {
                        ListViewItem item = new ListViewItem();
                        item.Text = str;
                        containsListView.Items.Add(item);
                    }
                    label1.Text = i.frequency.ToString();
                    break;
                }
        }
    }

    public class HotWord
    {
        public string word;
        public Int32 frequency;
        public List<string> music = new List<string>();
    }

}
