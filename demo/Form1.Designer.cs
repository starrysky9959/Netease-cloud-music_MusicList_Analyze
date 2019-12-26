namespace demo
{
    partial class Form1
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要修改
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.start = new System.Windows.Forms.Button();
            this.target = new System.Windows.Forms.TextBox();
            this.wordListView = new System.Windows.Forms.ListView();
            this.columnHeader1 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.columnHeader2 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.musicListView = new System.Windows.Forms.ListView();
            this.columnHeader3 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.label1 = new System.Windows.Forms.Label();
            this.containsListView = new System.Windows.Forms.ListView();
            this.searchButton = new System.Windows.Forms.Button();
            this.columnHeader4 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.SuspendLayout();
            // 
            // start
            // 
            this.start.Location = new System.Drawing.Point(58, 33);
            this.start.Name = "start";
            this.start.Size = new System.Drawing.Size(106, 61);
            this.start.TabIndex = 0;
            this.start.Text = "分析";
            this.start.UseVisualStyleBackColor = true;
            this.start.Click += new System.EventHandler(this.start_Click);
            // 
            // target
            // 
            this.target.Location = new System.Drawing.Point(225, 125);
            this.target.Name = "target";
            this.target.Size = new System.Drawing.Size(100, 25);
            this.target.TabIndex = 1;
            this.target.TextChanged += new System.EventHandler(this.target_TextChanged);
            // 
            // wordListView
            // 
            this.wordListView.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.columnHeader1,
            this.columnHeader2});
            this.wordListView.GridLines = true;
            this.wordListView.HideSelection = false;
            this.wordListView.Location = new System.Drawing.Point(28, 200);
            this.wordListView.Name = "wordListView";
            this.wordListView.Size = new System.Drawing.Size(284, 195);
            this.wordListView.TabIndex = 2;
            this.wordListView.UseCompatibleStateImageBehavior = false;
            this.wordListView.View = System.Windows.Forms.View.Details;
            // 
            // columnHeader1
            // 
            this.columnHeader1.Text = "单词";
            this.columnHeader1.Width = 120;
            // 
            // columnHeader2
            // 
            this.columnHeader2.Text = "词频";
            this.columnHeader2.Width = 106;
            // 
            // musicListView
            // 
            this.musicListView.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.columnHeader3});
            this.musicListView.GridLines = true;
            this.musicListView.HideSelection = false;
            this.musicListView.Location = new System.Drawing.Point(378, 12);
            this.musicListView.Name = "musicListView";
            this.musicListView.Size = new System.Drawing.Size(269, 407);
            this.musicListView.TabIndex = 3;
            this.musicListView.UseCompatibleStateImageBehavior = false;
            this.musicListView.View = System.Windows.Forms.View.Details;
            // 
            // columnHeader3
            // 
            this.columnHeader3.Text = "曲目";
            this.columnHeader3.Width = 117;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(257, 163);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(55, 15);
            this.label1.TabIndex = 4;
            this.label1.Text = "label1";
            // 
            // containsListView
            // 
            this.containsListView.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.columnHeader4});
            this.containsListView.GridLines = true;
            this.containsListView.HideSelection = false;
            this.containsListView.Location = new System.Drawing.Point(714, 72);
            this.containsListView.Name = "containsListView";
            this.containsListView.Size = new System.Drawing.Size(273, 288);
            this.containsListView.TabIndex = 5;
            this.containsListView.UseCompatibleStateImageBehavior = false;
            this.containsListView.View = System.Windows.Forms.View.Details;
            // 
            // searchButton
            // 
            this.searchButton.Location = new System.Drawing.Point(269, 53);
            this.searchButton.Name = "searchButton";
            this.searchButton.Size = new System.Drawing.Size(75, 23);
            this.searchButton.TabIndex = 6;
            this.searchButton.Text = "查找";
            this.searchButton.UseVisualStyleBackColor = true;
            this.searchButton.Click += new System.EventHandler(this.searchButton_Click);
            // 
            // columnHeader4
            // 
            this.columnHeader4.Text = "出现曲目";
            this.columnHeader4.Width = 223;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1079, 438);
            this.Controls.Add(this.searchButton);
            this.Controls.Add(this.containsListView);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.musicListView);
            this.Controls.Add(this.wordListView);
            this.Controls.Add(this.target);
            this.Controls.Add(this.start);
            this.Name = "Form1";
            this.Text = "Form1";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button start;
        private System.Windows.Forms.TextBox target;
        private System.Windows.Forms.ListView wordListView;
        private System.Windows.Forms.ColumnHeader columnHeader1;
        private System.Windows.Forms.ColumnHeader columnHeader2;
        private System.Windows.Forms.ListView musicListView;
        private System.Windows.Forms.ColumnHeader columnHeader3;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.ListView containsListView;
        private System.Windows.Forms.Button searchButton;
        private System.Windows.Forms.ColumnHeader columnHeader4;
    }
}

