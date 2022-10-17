<%@ Page Title="Project 3 - A5 TryIt" Language="C#" MasterPageFile="~/Site.Master" AutoEventWireup="true" CodeBehind="Default.aspx.cs" Inherits="TryIt._Default" %>

<asp:Content ID="BodyContent" ContentPlaceHolderID="MainContent" runat="server">
    <div>
        <h3>WebDownloading</h3>
        <h4>This service downloads the data from a given url and displays it below.</h4>
        <asp:Label ID="UrlLabel" runat="server" Text="Enter Url: "></asp:Label>
        <asp:TextBox ID="UrlInput" runat="server" placeholder="https://google.com"></asp:TextBox>
        <asp:Button ID="UrlSubmit" runat="server" Text="Download" OnClick="UrlSubmit_Click" />
        <br />
        <asp:Label ID="Label4" runat="server" Text=""></asp:Label>
    </div>
    <div>
        <h3>WeatherService</h3>
        <h4>This service gets the five day weather forecast based on a given zipcode and displays it below.</h4>
        <asp:Label ID="Label2" runat="server" Text="Enter Zipcode: "></asp:Label>
        <asp:TextBox ID="ZipcodeInput" runat="server" placeholder="85282"></asp:TextBox>
        <asp:Button ID="Button2" runat="server" Text="Get Weather" OnClick="GetWeather_Click" />
        <h5>Five Day Forecast</h5>
        <asp:Label ID="Label5" runat="server" Text=""></asp:Label>
    </div>
</asp:Content>
