﻿//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a tool.
//     Runtime Version:4.0.30319.42000
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------

namespace TryIt.AuthServiceReference {
    
    
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "4.0.0.0")]
    [System.ServiceModel.ServiceContractAttribute(ConfigurationName="AuthServiceReference.IService1")]
    public interface IService1 {
        
        [System.ServiceModel.OperationContractAttribute(Action="http://tempuri.org/IService1/Register", ReplyAction="http://tempuri.org/IService1/RegisterResponse")]
        string Register(string username, string password, string fullName, string email);
        
        [System.ServiceModel.OperationContractAttribute(Action="http://tempuri.org/IService1/Register", ReplyAction="http://tempuri.org/IService1/RegisterResponse")]
        System.Threading.Tasks.Task<string> RegisterAsync(string username, string password, string fullName, string email);
        
        [System.ServiceModel.OperationContractAttribute(Action="http://tempuri.org/IService1/Login", ReplyAction="http://tempuri.org/IService1/LoginResponse")]
        string Login(string username, string password);
        
        [System.ServiceModel.OperationContractAttribute(Action="http://tempuri.org/IService1/Login", ReplyAction="http://tempuri.org/IService1/LoginResponse")]
        System.Threading.Tasks.Task<string> LoginAsync(string username, string password);
        
        [System.ServiceModel.OperationContractAttribute(Action="http://tempuri.org/IService1/GetUser", ReplyAction="http://tempuri.org/IService1/GetUserResponse")]
        string GetUser(string username);
        
        [System.ServiceModel.OperationContractAttribute(Action="http://tempuri.org/IService1/GetUser", ReplyAction="http://tempuri.org/IService1/GetUserResponse")]
        System.Threading.Tasks.Task<string> GetUserAsync(string username);
    }
    
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "4.0.0.0")]
    public interface IService1Channel : TryIt.AuthServiceReference.IService1, System.ServiceModel.IClientChannel {
    }
    
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "4.0.0.0")]
    public partial class Service1Client : System.ServiceModel.ClientBase<TryIt.AuthServiceReference.IService1>, TryIt.AuthServiceReference.IService1 {
        
        public Service1Client() {
        }
        
        public Service1Client(string endpointConfigurationName) : 
                base(endpointConfigurationName) {
        }
        
        public Service1Client(string endpointConfigurationName, string remoteAddress) : 
                base(endpointConfigurationName, remoteAddress) {
        }
        
        public Service1Client(string endpointConfigurationName, System.ServiceModel.EndpointAddress remoteAddress) : 
                base(endpointConfigurationName, remoteAddress) {
        }
        
        public Service1Client(System.ServiceModel.Channels.Binding binding, System.ServiceModel.EndpointAddress remoteAddress) : 
                base(binding, remoteAddress) {
        }
        
        public string Register(string username, string password, string fullName, string email) {
            return base.Channel.Register(username, password, fullName, email);
        }
        
        public System.Threading.Tasks.Task<string> RegisterAsync(string username, string password, string fullName, string email) {
            return base.Channel.RegisterAsync(username, password, fullName, email);
        }
        
        public string Login(string username, string password) {
            return base.Channel.Login(username, password);
        }
        
        public System.Threading.Tasks.Task<string> LoginAsync(string username, string password) {
            return base.Channel.LoginAsync(username, password);
        }
        
        public string GetUser(string username) {
            return base.Channel.GetUser(username);
        }
        
        public System.Threading.Tasks.Task<string> GetUserAsync(string username) {
            return base.Channel.GetUserAsync(username);
        }
    }
}
