using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.Text;
using System.Threading.Tasks;

namespace UnrealModLauncher
{
    public class GameInfo
    {
        [JsonProperty("id")]
        public string Id { get; set; }

        [JsonProperty("name")]
        public string GameName { get; set; }

        [JsonProperty("path")]
        public string GamePath { get; set; }

        [JsonProperty("arguments")]
        public string Arguments { get; set; }

        public static GameInfo Create()
        {
            return new GameInfo()
            {
                Id = Guid.NewGuid().ToString()
            };
        }

        #region Overrides
        public override bool Equals(object obj)
        {
            if (obj is GameInfo)
            {
                var o = obj as GameInfo; 

                if (o.Id == Id) {
                    return true;
                }
            }

            return false;
        }

        public override int GetHashCode()
        {
            return Id.GetHashCode();
        }
        #endregion

        #region Operators
        public static bool operator == (GameInfo a, GameInfo b)
        {
            if (a.Id == b.Id)
            {
                return true;
            }

            return false;
        }

        public static bool operator !=(GameInfo a, GameInfo b)
        {
            if (a.Id != b.Id)
            {
                return true;
            }

            return false;
        }
        #endregion
    }
}
