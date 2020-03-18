using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using MySql.Data.MySqlClient;
using System.Windows.Forms;

namespace DetectGUIPlus
{
    class SQLInterface
    {
        //Shinco MYSQL
        //private readonly string SQL_CONNECT_STR = "Server=localhost;user id=root;password=$DQ43z9^w54&MRkn#@t!;Database=db_stategrid;Port=3306;charset=utf8;";
        //714 MYSQL
        private readonly string SQL_CONNECT_STR = "Server=localhost;user id=root;password=VWzN&dO0IHJMBB4BK#93;Database=db_stategrid;Port=3306;charset=utf8;";

        private MySqlConnection sqlCon = null;  // 数据库连接对象

        // 建立数据库连接
        public void connectDatabase()
        {
            sqlCon = new MySqlConnection(SQL_CONNECT_STR);
            try
            {
                sqlCon.Open();
                if (sqlCon.State.ToString() == "Open")
                {
                    Console.WriteLine("数据库连接成功");
                }
                else
                {
                    MessageBox.Show("数据库连接失败");
                }
            }
            catch(Exception ex)
            {
                MessageBox.Show("数据库连接不成功，原因:" + ex.Message);
            }         
        }

        // 断开数据库连接
        public void disconnectDatabase()
        {
            if (sqlCon.State.ToString() == "Open")
            {
                sqlCon.Close();

                if (sqlCon.State.ToString() == "Open")
                {
                    MessageBox.Show("数据库关闭失败");
                }
            }
        }

        // 返回数据库连接状态
        public bool sqlIsReady()
        {
            if (sqlCon.State.ToString() == "Open")
            {
                return true;
            }
            else
            {
                return false;
            } 
        }

        // SQL 查询所有room
        public List<string> readAllroom()
        {
            List<string> roomNames = new List<string>();
            MySqlCommand com = null;    //创建MYSQLCommand对象
            MySqlDataReader dataReader = null;  //创建MySqlDataReader对象
            com = new MySqlCommand("SELECT * FROM tb_room", sqlCon);
            dataReader = com.ExecuteReader();   //用ExcuteReader执行查询语句
            while(dataReader.Read())    //在while中读取每条记录
            {
                roomNames.Add(dataReader["name"].ToString());
            }

            dataReader.Close();
            return roomNames;
        }

        // SQL 根据roomname查询所有cabinet
        public List<string> readCabinetByRoom(string roomName)
        {
            List<string> cabinetNames = new List<string>();
            MySqlCommand com = null;    //创建MYSQLCommand对象
            MySqlDataReader dataReader = null;  //创建MySqlDataReader对象
            string sqlstr = "select * from tb_cabinet where room_id = (select id from tb_room where name = \'" + roomName + "\')";
            com = new MySqlCommand(sqlstr, sqlCon);
            dataReader = com.ExecuteReader();   //用ExcuteReader执行查询语句
            while (dataReader.Read())    //在while中读取每条记录
            {
                cabinetNames.Add(dataReader["name"].ToString());
            }

            dataReader.Close();
            return cabinetNames;
        }

        // SQL 根据roomname和cabinet查询所有device
        public List<string> readdeviceByRoomAndCabinet(string roomName, string cabinName)
        {
            List<string> deviceNames = new List<string>();
            MySqlCommand com = null;    //创建MYSQLCommand对象
            MySqlDataReader dataReader = null;  //创建MySqlDataReader对象
            string sqlstr = "SELECT * FROM db_stategrid.tb_device where cabinet_id = (select id from tb_cabinet where name = \'" + cabinName + "\' and room_id = (select id from tb_room where name = \'" + roomName + "\'))";
            com = new MySqlCommand(sqlstr, sqlCon);
            dataReader = com.ExecuteReader();   //用ExcuteReader执行查询语句
            while (dataReader.Read())    //在while中读取每条记录
            {
                deviceNames.Add(dataReader["name"].ToString());
            }

            dataReader.Close();
            return deviceNames;
        }

        // SQL Advanced查询(重载一：三个参数)
        public List<detectRecords> advanceQuery(string roomName, string cabName, string deviceName, string  DateStart, string DateStop)
        {
            List<detectRecords> result = new List<detectRecords>();
            MySqlCommand com = null;    //创建MYSQLCommand对象
            MySqlDataReader dataReader = null;  //创建MySqlDataReader对象
            string sqlstr = "select * from tb_records where detectDatetime between \'" + DateStart + "\' and \'" + DateStop + "\' and device_id = (select id from tb_device where name = '" + deviceName +"\' and cabinet_id = (select id from tb_cabinet where name = \'"+ cabName +"\' and room_id = (select id from tb_room where name = \'" + roomName + "\')));";
            com = new MySqlCommand(sqlstr, sqlCon);
            dataReader = com.ExecuteReader();   //用ExcuteReader执行查询语句
            while (dataReader.Read())    //在while中读取每条记录
            {
                result.Add(new detectRecords(dataReader["device_name"].ToString(),
                                             dataReader["detectClass"].ToString(),
                                             dataReader["detectResult"].ToString(),
                                             dataReader["detectAlarm"].ToString(),
                                             dataReader["detectDatetime"].ToString()));
            }

            dataReader.Close();
            return result;
        }

        // SQL Advanced查询(重载二：两个个参数)
        public List<detectRecords> advanceQuery(string roomName, string cabName, string DateStart, string DateStop)
        {
            List<detectRecords> result = new List<detectRecords>();
            MySqlCommand com = null;    //创建MYSQLCommand对象
            MySqlDataReader dataReader = null;  //创建MySqlDataReader对象
            string sqlstr = "select * from tb_records where detectDatetime between \'" + DateStart + "\' and \'" + DateStop + "\' and device_id  in (select id from tb_device where cabinet_id = (select id from tb_cabinet where name = \'" + cabName + "\' and room_id = (select id from tb_room where name = \'" + roomName + "\')))";
            com = new MySqlCommand(sqlstr, sqlCon);
            dataReader = com.ExecuteReader();   //用ExcuteReader执行查询语句
            while (dataReader.Read())    //在while中读取每条记录
            {
                result.Add(new detectRecords(dataReader["device_name"].ToString(),
                                             dataReader["detectClass"].ToString(),
                                             dataReader["detectResult"].ToString(),
                                             dataReader["detectAlarm"].ToString(),
                                             dataReader["detectDatetime"].ToString()));
            }

            dataReader.Close();
            return result;
        }

        // SQL Advanced查询(重载三：一个参数)
        public List<detectRecords> advanceQuery(string roomName, string DateStart, string DateStop)
        {
            List<detectRecords> result = new List<detectRecords>();
            MySqlCommand com = null;    //创建MYSQLCommand对象
            MySqlDataReader dataReader = null;  //创建MySqlDataReader对象
            string sqlstr = @"
                            select records.*, device.cabinname from 
                            (select * from tb_records where detectDatetime between '" + DateStart + @"' and '" + DateStop + @"' and device_id  in (select id from tb_device where cabinet_id in (select id from tb_cabinet where room_id = (select id from tb_room where name = '" + roomName + @"')))) as records,
                            (select tb_device.id as device_id, tb_device.name as devicename, tb_cabinet.name as cabinname from tb_device left join tb_cabinet on tb_device.cabinet_id = tb_cabinet.id) as device
                            where records.device_id = device.device_id 
                            ";
            com = new MySqlCommand(sqlstr, sqlCon);
            dataReader = com.ExecuteReader();   //用ExcuteReader执行查询语句
            while (dataReader.Read())    //在while中读取每条记录
            {
                result.Add(new detectRecords(dataReader["device_name"].ToString(),
                                             dataReader["detectClass"].ToString(),
                                             dataReader["detectResult"].ToString(),
                                             dataReader["detectAlarm"].ToString(),
                                             dataReader["detectDatetime"].ToString(),
                                             dataReader["cabinname"].ToString()));
            }

            dataReader.Close();
            return result;
        } 

        // SQL 插入检测结果,需要数据库名称与XML的名称对应起来
        public void insertRecord(string roomname,string cabinname, string devicename, string detectClass, string detectResult, string alert, string datetime)
        {
            MySqlCommand com = new MySqlCommand();      //创建MYSQLCommand对象
            com.Connection = sqlCon;                    //将sqlcon赋值给connection属性
            com.CommandText = @"insert into tb_records (device_id, device_name, detectClass, detectResult, detectAlarm, detectDatetime) VALUES
                              (
                              (select id from tb_device where name = '" + devicename + "' and cabinet_id = (select id from tb_cabinet where name = '" + cabinname + "' and room_id = (select id from tb_room where name = '" + roomname + @"'))),
                               '" + devicename + @"',
                               '" + detectClass + @"',
                               '" + detectResult + @"',
                               '" + alert + @"',
                               '" + datetime + "')";
            int i = com.ExecuteNonQuery();  // i 为 返回插入的记录数
            if (i > 0)
            {
                Console.WriteLine("插入成功");
            }
        }
    }


    // 类detectRecords用于检测记录的查询
    public class detectRecords
    {
        private string _deviceName;

        private string _detectClass;

        private string _detectResult;

        private string _detectAlarm;

        private string _detectDatetime;

        private string _cabinetName;

        public detectRecords(string dN, string dC, string dR, string dA, string dD)
        {
            this._deviceName = dN;
            this._detectClass = dC;
            this._detectResult = dR;
            this._detectAlarm = dA;
            this._detectDatetime = dD;
        }

        public detectRecords(string dN, string dC, string dR, string dA, string dD, string dCab)
        {
            this._deviceName = dN;
            this._detectClass = dC;
            this._detectResult = dR;
            this._detectAlarm = dA;
            this._detectDatetime = dD;
            this._cabinetName = dCab;
        }

        public string deviceName
        {
            get { return _deviceName; }
        }

        public string detectClass
        {
            get { return _detectClass; }
        }

        public string detectResult
        {
            get { return _detectResult; }
        }

        public string detectAlarm
        {
            get { return _detectAlarm; }
        }

        public string detectDatetime
        {
            get { return _detectDatetime; }
        }

        public string cabinetName
        {
            get { return _cabinetName; }
        }

    }
}
