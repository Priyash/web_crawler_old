using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Data.SqlClient;
using System.Data;

namespace DB_Connect
{
    class DB_Handler
    {
        string connString ="Data Source=PRIYASH\\SQLEXPRESS; Initial Catalog=TEST;Integrated Security = SSPI;User ID=PRIYASH\\PRIYASH_11;Password=3324383606";
        SqlConnection conn;
        List<string> words;
        string _path = "C:\\Users\\PRIYASH_11\\Desktop\\XML data\\";
        string file = "Word.txt";
        string path;
        public DB_Handler()
        {
            conn = new SqlConnection(connString);
            conn.Open();
            words = new List<string>();
            path = _path + file;
            readFile();
        }

        //READ ALL THE WORDS FROM THE TEXT FILE 
        void readFile()
        {
            using(StreamReader reader = new StreamReader(path))
            {
                string line;
                while((line=reader.ReadLine())!=null)
                {
                    words.Add(line);
                }
            }
        }

        //PUSHING THE WORDS INTO THE DATABASE
        public void pushData()
        {
            if(conn.State.ToString()=="Closed")
            {
                conn.Open();
            }

            string query = "INSERT INTO InvertedIndex(Word) VALUES(@Word)";
            for(int i = 0;i<words.Count;i++)
            {

            SqlCommand cmd = new SqlCommand(query,conn);
            cmd.Parameters.Add("@Word", SqlDbType.VarChar).Value = words[i].ToString();
            cmd.ExecuteNonQuery();
            }
        }

        public void cleanData()
        {
            if (conn.State.ToString() == "Closed")
            {
                conn.Open();
            }

            string query = "DELETE InvertedIndex";
            SqlCommand cmd = new SqlCommand(query,conn);
            cmd.ExecuteNonQuery();

            if (conn.State.ToString() == "Closed")
            {
                conn.Open();
            }

            //THIS QUERY IS USED TO RESET THE AUTO_INCREMENT VALUE
            string query2 = "DBCC CHECKIDENT ('TEST.dbo.InvertedIndex', RESEED, 0)";
            SqlCommand cmd2 = new SqlCommand(query2, conn);
            cmd2.ExecuteNonQuery();
        }

    }
}
