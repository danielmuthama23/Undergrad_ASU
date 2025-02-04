﻿//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a tool.
//     Runtime Version:4.0.30319.42000
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------

namespace TryIt.TravelServiceReference {
    
    
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "4.0.0.0")]
    [System.ServiceModel.ServiceContractAttribute(ConfigurationName="TravelServiceReference.IService1")]
    public interface IService1 {
        
        [System.ServiceModel.OperationContractAttribute(Action="http://tempuri.org/IService1/GetHotels", ReplyAction="http://tempuri.org/IService1/GetHotelsResponse")]
        string[] GetHotels(string zipcode);
        
        [System.ServiceModel.OperationContractAttribute(Action="http://tempuri.org/IService1/GetHotels", ReplyAction="http://tempuri.org/IService1/GetHotelsResponse")]
        System.Threading.Tasks.Task<string[]> GetHotelsAsync(string zipcode);
        
        [System.ServiceModel.OperationContractAttribute(Action="http://tempuri.org/IService1/GetRestaurants", ReplyAction="http://tempuri.org/IService1/GetRestaurantsResponse")]
        string[] GetRestaurants(string zipcode);
        
        [System.ServiceModel.OperationContractAttribute(Action="http://tempuri.org/IService1/GetRestaurants", ReplyAction="http://tempuri.org/IService1/GetRestaurantsResponse")]
        System.Threading.Tasks.Task<string[]> GetRestaurantsAsync(string zipcode);
    }
    
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "4.0.0.0")]
    public interface IService1Channel : TryIt.TravelServiceReference.IService1, System.ServiceModel.IClientChannel {
    }
    
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "4.0.0.0")]
    public partial class Service1Client : System.ServiceModel.ClientBase<TryIt.TravelServiceReference.IService1>, TryIt.TravelServiceReference.IService1 {
        
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
        
        public string[] GetHotels(string zipcode) {
            return base.Channel.GetHotels(zipcode);
        }
        
        public System.Threading.Tasks.Task<string[]> GetHotelsAsync(string zipcode) {
            return base.Channel.GetHotelsAsync(zipcode);
        }
        
        public string[] GetRestaurants(string zipcode) {
            return base.Channel.GetRestaurants(zipcode);
        }
        
        public System.Threading.Tasks.Task<string[]> GetRestaurantsAsync(string zipcode) {
            return base.Channel.GetRestaurantsAsync(zipcode);
        }
    }
}
