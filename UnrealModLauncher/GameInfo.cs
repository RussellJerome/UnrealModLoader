using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.Text;
using System.Threading.Tasks;

namespace UnrealModLauncher
{
    [DataContract]
    public class GameInfo
    {
        [DataMember]
        public string GameName { get; set; }
        [DataMember]
        public string GamePath { get; set; }
        [DataMember]
        public string Arguments { get; set; }
        [DataMember]
        public bool AutoInject { get; set; }
    }
}
