<%@ Page Title="Home Page" Language="C#" MasterPageFile="~/Site.Master" AutoEventWireup="true" CodeBehind="Default.aspx.cs" Inherits="WebApplication._Default" %>

<asp:Content ID="BodyContent" ContentPlaceHolderID="MainContent" runat="server">
    <asp:Label ID="Test" runat="server"></asp:Label>

    <h4>Table</h4>
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
            <td class="tg-0lax" colspan="4">Percentage of contribution: Tyler Fichiera: 100%</td>
          </tr>
          <tr>
            <td class="tg-1wig">Provider Name</td>
            <td class="tg-1wig">Page and Component Type</td>
            <td class="tg-1wig">Component Description</td>
            <td class="tg-1wig">Resources and Methods</td>
          </tr>
          <tr>
            <td class="tg-0lax">Tyler Fichiera</td>
            <td class="tg-0lax"></td>
            <td class="tg-0lax"></td>
            <td class="tg-0lax"></td>
          </tr>
          <tr>
            <td class="tg-0lax">Tyler Fichiera</td>
            <td class="tg-0lax"></td>
            <td class="tg-0lax"></td>
            <td class="tg-0lax"></td>
          </tr>
          <tr>
            <td class="tg-0lax">Tyler Fichiera</td>
            <td class="tg-0lax"></td>
            <td class="tg-0lax"></td>
            <td class="tg-0lax"></td>
          </tr>
          <tr>
            <td class="tg-0lax">Tyler Fichiera</td>
            <td class="tg-0lax"></td>
            <td class="tg-0lax"></td>
            <td class="tg-0lax"></td>
          </tr>
        </tbody>
        </table>
    </div>

</asp:Content>
