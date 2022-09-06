<%@ Page Title="Home Page" Language="C#" MasterPageFile="~/Site.Master" AutoEventWireup="true" CodeBehind="Default.aspx.cs" Inherits="TempConversionWebApplication._Default" %>

<asp:Content ID="BodyContent" ContentPlaceHolderID="MainContent" runat="server">
    <br />
    <asp:TextBox ID="TextBox1" runat="server" Height="23px" Width="120px"></asp:TextBox>
    <br />
    <asp:Label ID="Label1" runat="server" Text="Convert to:"></asp:Label>
    <asp:DropDownList ID="DropDownList1" runat="server">
        <asp:ListItem>Celsius</asp:ListItem>
        <asp:ListItem>Fahrenheit</asp:ListItem>
    </asp:DropDownList>
    <br/>
    <asp:Button ID="Button1" runat="server" Text="Convert" OnClick="Button1_Click" />
<asp:Label ID="Label2" runat="server" Text="Conversion:"></asp:Label>
</asp:Content>
