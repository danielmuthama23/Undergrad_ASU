﻿//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a tool.
//     Runtime Version:4.0.30319.42000
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------

namespace TempConversionWindowsFormsApp.TempService {
    
    
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "4.0.0.0")]
    [System.ServiceModel.ServiceContractAttribute(ConfigurationName="TempService.ITempService")]
    public interface ITempService {
        
        [System.ServiceModel.OperationContractAttribute(Action="http://tempuri.org/ITempService/c2f", ReplyAction="http://tempuri.org/ITempService/c2fResponse")]
        int c2f(int c);
        
        [System.ServiceModel.OperationContractAttribute(Action="http://tempuri.org/ITempService/c2f", ReplyAction="http://tempuri.org/ITempService/c2fResponse")]
        System.Threading.Tasks.Task<int> c2fAsync(int c);
        
        [System.ServiceModel.OperationContractAttribute(Action="http://tempuri.org/ITempService/f2c", ReplyAction="http://tempuri.org/ITempService/f2cResponse")]
        int f2c(int f);
        
        [System.ServiceModel.OperationContractAttribute(Action="http://tempuri.org/ITempService/f2c", ReplyAction="http://tempuri.org/ITempService/f2cResponse")]
        System.Threading.Tasks.Task<int> f2cAsync(int f);
    }
    
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "4.0.0.0")]
    public interface ITempServiceChannel : TempConversionWindowsFormsApp.TempService.ITempService, System.ServiceModel.IClientChannel {
    }
    
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "4.0.0.0")]
    public partial class TempServiceClient : System.ServiceModel.ClientBase<TempConversionWindowsFormsApp.TempService.ITempService>, TempConversionWindowsFormsApp.TempService.ITempService {
        
        public TempServiceClient() {
        }
        
        public TempServiceClient(string endpointConfigurationName) : 
                base(endpointConfigurationName) {
        }
        
        public TempServiceClient(string endpointConfigurationName, string remoteAddress) : 
                base(endpointConfigurationName, remoteAddress) {
        }
        
        public TempServiceClient(string endpointConfigurationName, System.ServiceModel.EndpointAddress remoteAddress) : 
                base(endpointConfigurationName, remoteAddress) {
        }
        
        public TempServiceClient(System.ServiceModel.Channels.Binding binding, System.ServiceModel.EndpointAddress remoteAddress) : 
                base(binding, remoteAddress) {
        }
        
        public int c2f(int c) {
            return base.Channel.c2f(c);
        }
        
        public System.Threading.Tasks.Task<int> c2fAsync(int c) {
            return base.Channel.c2fAsync(c);
        }
        
        public int f2c(int f) {
            return base.Channel.f2c(f);
        }
        
        public System.Threading.Tasks.Task<int> f2cAsync(int f) {
            return base.Channel.f2cAsync(f);
        }
    }
}
