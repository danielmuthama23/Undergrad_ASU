﻿<%@ Page Title="Contact" Language="C#" MasterPageFile="~/Site.Master" AutoEventWireup="true" CodeBehind="Staff.aspx.cs" Inherits="WebApplication.Contact" %>

<asp:Content ID="BodyContent" ContentPlaceHolderID="MainContent" runat="server">
    <% if (HttpContext.Current.User.IsInRole("Staff")) {%>
        <h3>Staff</h3>
        <h4>Add Staff</h4>
        <p>Only administrators are allowed to perform this action</p>
        <asp:Label ID="Label1" runat="server" Text="Username:"></asp:Label>
        <asp:TextBox ID="StaffUsernameInput" runat="server"></asp:TextBox>
        <br />
        <asp:Label ID="Label2" runat="server" Text="Password**:"></asp:Label>
        <asp:TextBox ID="StaffPasswordInput" TextMode="Password" runat="server"></asp:TextBox>
        <br />
        <asp:Label ID="Label3" runat="server" Text="Full Name:"></asp:Label>
        <asp:TextBox ID="StaffFullNameInput" runat="server"></asp:TextBox>
        <br />
        <asp:Label ID="Label4" runat="server" Text="Email:"></asp:Label>
        <asp:TextBox ID="StaffEmailInput" TextMode="Email" runat="server"></asp:TextBox>
        <br />
        <asp:Label ID="Label5" runat="server" Text="** Password must have at least one uppercase, one number, and be at least 8 characters long"></asp:Label>
        <br />
        <asp:Button ID="AddStaffButton" runat="server" Text="Add Staff Member" OnClick="AddStaffButton_Click" />
        <asp:Label ID="StaffAddResponse" runat="server" Text=""></asp:Label>

        <h4>Get Weather Info</h4>
        <h4>This service gets the five day weather forecast based on a given zipcode and displays it below.</h4>
        <asp:Label ID="Label6" runat="server" Text="Enter Zipcode: "></asp:Label>
        <asp:TextBox ID="ZipcodeInput" runat="server" placeholder="85282"></asp:TextBox>
        <asp:Button ID="Button2" runat="server" Text="Get Weather" OnClick="GetWeather_Click" />
        <h5>Five Day Forecast</h5>
        <asp:Label ID="Label7" runat="server" Text=""></asp:Label>
    <% } else { %>
        <h3>You do not have access to this page.</h3>
        <p>Please login with staff credentials to view this page</p>
    <% } %>
</asp:Content>
