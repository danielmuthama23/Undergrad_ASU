﻿//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a tool.
//     Runtime Version:4.0.30319.42000
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------

namespace TryIt.WebDownloadingService {
    
    
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "4.0.0.0")]
    [System.ServiceModel.ServiceContractAttribute(ConfigurationName="WebDownloadingService.WebDownloadingService")]
    public interface WebDownloadingService {
        
        [System.ServiceModel.OperationContractAttribute(Action="http://tempuri.org/WebDownloadingService/WebDownload", ReplyAction="http://tempuri.org/WebDownloadingService/WebDownloadResponse")]
        string WebDownload(string url);
        
        [System.ServiceModel.OperationContractAttribute(Action="http://tempuri.org/WebDownloadingService/WebDownload", ReplyAction="http://tempuri.org/WebDownloadingService/WebDownloadResponse")]
        System.Threading.Tasks.Task<string> WebDownloadAsync(string url);
    }
    
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "4.0.0.0")]
    public interface WebDownloadingServiceChannel : TryIt.WebDownloadingService.WebDownloadingService, System.ServiceModel.IClientChannel {
    }
    
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "4.0.0.0")]
    public partial class WebDownloadingServiceClient : System.ServiceModel.ClientBase<TryIt.WebDownloadingService.WebDownloadingService>, TryIt.WebDownloadingService.WebDownloadingService {
        
        public WebDownloadingServiceClient() {
        }
        
        public WebDownloadingServiceClient(string endpointConfigurationName) : 
                base(endpointConfigurationName) {
        }
        
        public WebDownloadingServiceClient(string endpointConfigurationName, string remoteAddress) : 
                base(endpointConfigurationName, remoteAddress) {
        }
        
        public WebDownloadingServiceClient(string endpointConfigurationName, System.ServiceModel.EndpointAddress remoteAddress) : 
                base(endpointConfigurationName, remoteAddress) {
        }
        
        public WebDownloadingServiceClient(System.ServiceModel.Channels.Binding binding, System.ServiceModel.EndpointAddress remoteAddress) : 
                base(binding, remoteAddress) {
        }
        
        public string WebDownload(string url) {
            return base.Channel.WebDownload(url);
        }
        
        public System.Threading.Tasks.Task<string> WebDownloadAsync(string url) {
            return base.Channel.WebDownloadAsync(url);
        }
    }
}
