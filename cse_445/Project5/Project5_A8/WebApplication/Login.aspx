<%@ Page Title="Login" Language="C#" MasterPageFile="~/Site.Master" AutoEventWireup="true" CodeBehind="Login.aspx.cs" Inherits="WebApplication.Login" %>

<asp:Content ID="BodyContent" ContentPlaceHolderID="MainContent" runat="server">
    <h3>Login</h3>
    <asp:Label ID="Label6" runat="server" Text="Username:"></asp:Label>
    <asp:TextBox ID="UsernameLoginInput" runat="server"></asp:TextBox>
    <br />
    <asp:Label ID="Label7" runat="server" Text="Password:"></asp:Label>
    <asp:TextBox ID="PasswordLoginInput" TextMode="Password" runat="server"></asp:TextBox>
    <br />
    <asp:Label ID="Label9" runat="server" Text="Remember Me?"></asp:Label>
    <asp:CheckBox ID="RememberMe" runat="server" />
    <br />
    <asp:Image ID="VerifierImage" runat="server" />
    <asp:TextBox ID="ImageVerifyText" runat="server" ></asp:TextBox>
    <br />
    <asp:Button ID="LoginButton" runat="server" Text="Login" OnClick="LoginButton_Click" />
    <asp:Label ID="Label10" runat="server">
        or <a href="Register.aspx">register here</a>
    </asp:Label>
    <br />
    <asp:Label ID="LoginResMessage" runat="server" Text=""></asp:Label>
</asp:Content>
