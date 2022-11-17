<%@ Page Title="Register" Language="C#" MasterPageFile="~/Site.Master" AutoEventWireup="true" CodeBehind="Register.aspx.cs" Inherits="WebApplication.Register" %>

<asp:Content ID="BodyContent" ContentPlaceHolderID="MainContent" runat="server">
    <h3>Register</h3>
    <asp:Label ID="Label1" runat="server" Text="Username:"></asp:Label>
    <asp:TextBox ID="UsernameInput" runat="server"></asp:TextBox>
    <br />
    <asp:Label ID="Label2" runat="server" Text="Password**:"></asp:Label>
    <asp:TextBox ID="PasswordInput" TextMode="Password" runat="server"></asp:TextBox>
    <br />
    <asp:Label ID="Label3" runat="server" Text="Full Name:"></asp:Label>
    <asp:TextBox ID="FullNameInput" runat="server"></asp:TextBox>
    <br />
    <asp:Label ID="Label4" runat="server" Text="Email:"></asp:Label>
    <asp:TextBox ID="EmailInput" TextMode="Email" runat="server"></asp:TextBox>
    <br />
    <asp:Label ID="Label5" runat="server" Text="** Password must have at least one uppercase, one number, and be at least 8 characters long"></asp:Label>
    <br />
    <asp:Button ID="RegisterButton" runat="server" Text="Register" OnClick="RegisterButton_Click" />
    <asp:Label ID="RegisterResLabel" runat="server" Text=""></asp:Label>
</asp:Content>
