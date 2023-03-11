using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;

namespace AWSDynamoDB
{
	public class Config
	{
		private const string FilePath = "./config.json";

		public bool IsUseLocalDB { get; set; }

		public string Profile { get; set; }

		public string AccessKey { get; set; }

		public string SecretKey { get; set; }

		public string RegionName { get; set; }

		public string ServiceURL { get; set; }

		//private static Config m_config = new Config();

		private static readonly Lazy<Config> m_config = new Lazy<Config>((Func<Config>)(() => new Config()));


		public Config()
		{
			loadConfig(FilePath);
		}

		private void loadConfig(string filePath)
		{
			var loaded_json = JObject.Parse(File.ReadAllText(FilePath));
			if (null == loaded_json)
			{
				Console.WriteLine($"Not found Config File !!! : {FilePath}");
				return;
			}

			var found_is_use_local_db = loaded_json[(object)"isUseLocalDB"].Value<bool>();
			if(true == found_is_use_local_db)
			{
				var found_local_db = loaded_json[(object)"LocalDB"];
				if (null == found_local_db)
				{
					Console.WriteLine($"Not found LocalDB key in Config File !!! : {FilePath}");
					return;
				}

				IsUseLocalDB = found_is_use_local_db;
				ServiceURL = found_local_db[(object)"ServiceURL"].Value<string>();
			}
			else
			{
				var found_aws = loaded_json[(object)"AWS"];
				if (null == found_aws)
				{
					Console.WriteLine($"Not found AWS key in Config File !!! : {FilePath}");
					return;
				}

				Profile = found_aws[(object)"Profile"].Value<string>();
				AccessKey = found_aws[(object)"AccessKey"].Value<string>();
				SecretKey = found_aws[(object)"SecretKey"].Value<string>();
				RegionName = found_aws[(object)"Region"].Value<string>();
				ServiceURL = found_aws[(object)"ServiceURL"].Value<string>();
			}
		}

		public static Config getInstance() { return Config.m_config.Value; }
	}
}
