using System;
using Newtonsoft.Json;

namespace SDKWrapperJsonValue
{
    [JsonObject(MemberSerialization.OptOut)]
    public class search_device_json
    {
        [JsonProperty(PropertyName = "oem type")]
        public string oem_type { get; set; }
    }

    [JsonObject(MemberSerialization.OptOut)]
    public class device_login_json
    {
        [JsonProperty(PropertyName = "ip or id")]
        public string ip_or_id { get; set; }

        [JsonProperty(PropertyName = "media port")]
        public int media_port { get; set; }

        [JsonProperty(PropertyName = "user")]
        public string user { get; set; }

        [JsonProperty(PropertyName = "password")]
        public string password { get; set; }

        [JsonProperty(PropertyName = "ddns id server addr")]
        public string ddns_id_server_addr { get; set; }

        [JsonProperty(PropertyName = "p2p type")]
        public string p2p_type { get; set; }

        [JsonProperty(PropertyName = "oem type")]
        public string oem_type { get; set; }
    }

    [JsonObject(MemberSerialization.OptOut)]
    public class start_preview_json
    {
        [JsonProperty(PropertyName = "channel")]
        public int channel { get; set; }

        [JsonProperty(PropertyName = "stream type")]
        public string stream_type { get; set; }

        [JsonProperty(PropertyName = "auto connect")]
        public bool auto_connect { get; set; }
    }
}
