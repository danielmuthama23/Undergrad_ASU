<%@ Page Title="Home Page" Language="C#" MasterPageFile="~/Site.Master" AutoEventWireup="true" CodeBehind="Default.aspx.cs" Inherits="TryIt._Default" %>

<asp:Content ID="BodyContent" ContentPlaceHolderID="MainContent" runat="server">
    <h1>Authentication Service</h1>
    <div>
        <h3>Register</h3>
        <p>Register account below using usernam, password, full name, and email.</p>
        <p>Method: string Register(string username, string password, string fullName, string email)</p>
        <p>This service is located at: http://webstrar56.fulton.asu.edu/Page0/Service1.svc?wsdl</p>
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
    </div>
    <div>
        <h3>Login</h3>
        <p>Login to account using username and password.</p>
        <p>Method: string Login(string username, string password)</p>
        <p>This service is located at: http://webstrar56.fulton.asu.edu/Page0/Service1.svc?wsdl</p>
        <asp:Label ID="Label6" runat="server" Text="Username:"></asp:Label>
        <asp:TextBox ID="UsernameLoginInput" runat="server"></asp:TextBox>
        <br />
        <asp:Label ID="Label7" runat="server" Text="Password**:"></asp:Label>
        <asp:TextBox ID="PasswordLoginInput" TextMode="Password" runat="server"></asp:TextBox>
        <br />
        <asp:Label ID="Label8" runat="server" Text="** Password must have at least one uppercase, one number, and be at least 8 characters long"></asp:Label>
        <br />
        <asp:Button ID="LoginButton" runat="server" Text="Login" OnClick="LoginButton_Click" />
        <asp:Label ID="LoginResLabel" runat="server" Text=""></asp:Label>
    </div>
    <div>
        <h3>Get User Account</h3>
        <p>Get the account info of the person currently logged in (stored in cookies).</p>
        <p>Method: string GetUser(string username)</p>
        <p>This service is located at: http://webstrar56.fulton.asu.edu/Page0/Service1.svc?wsdl</p>
        <asp:Button ID="GetUserButton" runat="server" Text="Get User" OnClick="GetUserButton_Click" />
        <br />
        <asp:Label ID="AccountInfoLabel" runat="server" Text=""></asp:Label>
    </div>
    <h1>Travel Service</h1>
    <div>
        <h3>Get Hotels Near Zipcode</h3>
        <p>Get hotels near a given zipcode that are within a 15 minute drive</p>
        <p>Method: string[] GetHotels(string zipcode)</p>
        <p>This service is located at: http://webstrar56.fulton.asu.edu/Page1/Service1.svc?wsdl</p>
        <asp:Label ID="Label10" runat="server" Text="Zipcode:"></asp:Label>
        <asp:TextBox ID="HotelZipcodeInput" runat="server" placeholder="90035"></asp:TextBox>
        <br />
        <asp:Button ID="GetHotels" runat="server" Text="Get Hotels" OnClick="GetHotels_Click" />
        <br />
        <asp:Label ID="HotelsLabel" runat="server" Text=""></asp:Label>
    </div>
    <div>
        <h3>Get Restaurants Near Zipcode</h3>
        <p>Get hotels near a given zipcode that are within a 500 meter radius</p>
        <p>Method: string[] GetRestaurants(string zipcode)</p>
        <p>This service is located at: http://webstrar56.fulton.asu.edu/Page1/Service1.svc?wsdl</p>
        <asp:Label ID="Label11" runat="server" Text="Zipcode:"></asp:Label>
        <asp:TextBox ID="RestaurantZipcodeInput" runat="server" placeholder="90035"></asp:TextBox>
        <br />
        <asp:Button ID="GetRestaurants" runat="server" Text="Get Restaurants" OnClick="GetRestaurants_Click" />
        <br />
        <asp:Label ID="RestaurantsLabel" runat="server" Text=""></asp:Label>
    </div>
</asp:Content>
