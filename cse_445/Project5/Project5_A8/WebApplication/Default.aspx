<%@ Page Title="Home Page" Language="C#" MasterPageFile="~/Site.Master" AutoEventWireup="true" CodeBehind="Default.aspx.cs" Inherits="WebApplication._Default" %>

<asp:Content ID="BodyContent" ContentPlaceHolderID="MainContent" runat="server">
    <h4>How the Application Works</h4>
    <p>This project is split up into six pages:</p>
    <ul>
        <li>Default (this page): explains the project and has a service directory. Anyone can access this page without a login.</li>
        <li>Profile Page: Logged in members can access this with the username button in the menu bar at the top.</li>
        <li>Member Page: Members and Staff can access this page and are able to test the crypt dll, convert currency, and translate text between languages.</li>
        <li>Staff Page: Only staff are able to access this page and it gives admins the option to add other staff by creating an account for them and also getting a five day weather forecast from a zipcode.</li>
        <li>Login Page: Accessed by the login button on the menu bar above or by trying to access a restricted page when not signed in.</li>
        <li>Register Page: Can be access through the login page.</li>
    </ul>
    <p>Logins to test:</p>
    <ul>
        <li>For Member access: <b>member1</b> / <b>Password123</b></li>
        <li>For Staff access: <b>TA</b> / <b>Cse44598!</b></li>
        <li>For Admin access: <b>admin1</b> / <b>Password123</b></li>
    </ul>

    <h4>Service Directory</h4>
    <div>
        <style type="text/css">
        .tg  {border-collapse:collapse;border-spacing:0;}
        .tg td{border-color:black;border-style:solid;border-width:1px;font-family:Arial, sans-serif;font-size:14px;
          overflow:hidden;padding:10px 5px;word-break:normal;}
        .tg th{border-color:black;border-style:solid;border-width:1px;font-family:Arial, sans-serif;font-size:14px;
          font-weight:normal;overflow:hidden;padding:10px 5px;word-break:normal;}
        .tg .tg-1wig{font-weight:bold;text-align:left;vertical-align:top}
        .tg .tg-baqh{text-align:center;vertical-align:top}
        .tg .tg-0lax{text-align:left;vertical-align:top}
        </style>
        <table class="tg">
        <thead>
          <tr>
            <th class="tg-baqh" colspan="4"><span style="font-weight:bold">Application and Components Summary Table</span></th>
          </tr>
        </thead>
        <tbody>
          <tr>
            <td class="tg-0lax" colspan="4">This application is deployed at: <a href="http://google.com/">http://google.com</a></td>
          </tr>
          <tr>
            <td class="tg-0lax" colspan="4">Percentage of contribution: Tyler Fichiera: 50%, Ethan Robinson: 50%</td>
          </tr>
          <tr>
            <td class="tg-1wig">Provider Name</td>
            <td class="tg-1wig">Page and Component Type</td>
            <td class="tg-1wig">Component Description</td>
            <td class="tg-1wig">Resources and Methods</td>
          </tr>
          <tr>
            <td class="tg-0lax">Tyler Fichiera</td>
            <td class="tg-0lax">Encrypt/Decrypt DLL</td>
            <td class="tg-0lax">Encrypts and Decrypts raw text. The two methods, Encrypt and Decrypt both take in a string and output a string.</td>
            <td class="tg-0lax">The Crypt class library uses System.Security.Cryptography for base64 conversion. It is used to save users to XML files and can be tested manually on the Member.aspx page.</td>
          </tr>
          <tr>
            <td class="tg-0lax">Tyler Fichiera</td>
            <td class="tg-0lax">XML files (Member.xml & Staff.xml)</td>
            <td class="tg-0lax">Stores the username, encrypted password, full name, and email of register members & staff</td>
            <td class="tg-0lax">Used for the login and registration. Handled by custom methods used to add and search based on given inputs of username and password.</td>
          </tr>
          <tr>
            <td class="tg-0lax">Tyler Fichiera</td>
            <td class="tg-0lax">Cookies / Auth</td>
            <td class="tg-0lax">Stores the userID of the logged in user. The inputs are the username and also whether the username should be shared between sessions.</td>
            <td class="tg-0lax">This is handled using asp.net's FormsAuthentication library which helps handle the authentication and access control page by page. (The logic is commented inside Web.config)</td>
          </tr>
          <tr>
            <td class="tg-0lax">Tyler Fichiera</td>
            <td class="tg-0lax">User Control</td>
            <td class="tg-0lax">Login and Registration image verification (captcha) used to prevent spam. Input is the text in the image (5 chars) and the output is boolean for whether it is valid or not.</td>
            <td class="tg-0lax">This can be tested on either the login or registration page. This uses the rest api supplied by ASU for generating the images with given text input.</td>
          </tr>
          <tr>
            <td class="tg-0lax">Tyler Fichiera</td>
            <td class="tg-0lax">Weather Service</td>
            <td class="tg-0lax">Output the five day forecast from an inputted zipcode.</td>
            <td class="tg-0lax">This uses the weather.visualcrossing.com rest api to retrieve the coordinates of a zipcode and the weather from those coordinates. This can be tested on the staff page.</td>
          </tr>
          <tr>
            <td class="tg-0lax">Ethan Robinson</td>
            <td class="tg-0lax">appSettings</td>
            <td class="tg-0lax">Stores the admins in a field called ADMINS which is hardcoded.</td>
            <td class="tg-0lax">This is fetched by the staff page to tell who should be allowed to add staff using the GUI. The gui is disabled if the current staff member is not in ADMINS.</td>
          </tr>
          <tr>
            <td class="tg-0lax">Ethan Robinson</td>
            <td class="tg-0lax">ASPX Pages</td>
            <td class="tg-0lax">Member and Staff page with remote and dll services.</td>
            <td class="tg-0lax">Gui design with integrated services</td>
          </tr>
            <tr>
            <td class="tg-0lax">Ethan Robinson</td>
            <td class="tg-0lax">Global.aspx event handler</td>
            <td class="tg-0lax">Active users event handler and count variable</td>
            <td class="tg-0lax">UserCount variable used in Application_Start and Session_Start to track how many users are online</td>
          </tr>
            <tr>
            <td class="tg-0lax">Ethan Robinson</td>
            <td class="tg-0lax">TextTranslate Service</td>
            <td class="tg-0lax">Translate a text to desired language</td>
            <td class="tg-0lax">use TransLate(string, string) to take in original text as input string and output text in desired language in a string</td>
          </tr>
            <tr>
            <td class="tg-0lax">Ethan Robinson</td>
            <td class="tg-0lax">CurrencyConverter</td>
            <td class="tg-0lax">convert currency to amount in different currency </td>
            <td class="tg-0lax">Use Convert(string, string, double) to take in two different currencies as strings one is  and outputting the new amount as a double</td>
          </tr>
        </tbody>
        </table>
    </div>

    <h4>Number of Active Users</h4>
    <asp:Label ID="ActiveUsers" runat="server" Text=""></asp:Label>
</asp:Content>
