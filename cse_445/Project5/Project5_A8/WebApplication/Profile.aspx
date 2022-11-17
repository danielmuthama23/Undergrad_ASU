<%@ Page Title="Contact" Language="C#" MasterPageFile="~/Site.Master" AutoEventWireup="true" CodeBehind="Profile.aspx.cs" Inherits="WebApplication.Profile" %>

<asp:Content ID="BodyContent" ContentPlaceHolderID="MainContent" runat="server">
    <h3>Profile</h3>
    <h4>Welcome, <%= HttpContext.Current.User.Identity.Name %>!</h4>
    <p>Username: <%= HttpContext.Current.User.Identity.Name %></p>
    <p>Email: </p>
    <p>Account Type: <%= Providers.Handler.CurrentRole %></p>
</asp:Content>
