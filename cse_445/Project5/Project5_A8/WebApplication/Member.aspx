<%@ Page Title="About" Language="C#" MasterPageFile="~/Site.Master" AutoEventWireup="true" CodeBehind="Member.aspx.cs" Inherits="WebApplication.Member" %>

<asp:Content ID="BodyContent" ContentPlaceHolderID="MainContent" runat="server">
    <h3>Member</h3>

    <!-- Encrypt / Decrypt Access Point - Tyler Fichiera -->
    <h4>Encrypt / Decrypt Access Point</h4>
    <p>Proof that the Encrypt / Decrypt DLL works</p>
    <asp:Label ID="Label5" runat="server" Text="Raw Text:"></asp:Label>
    <asp:TextBox ID="RawInput" runat="server"></asp:TextBox>
    <br />
    <asp:Button ID="EncryptButton" runat="server" Text="Encrypt" OnClick="EncryptButton_Click" />
    <asp:Button ID="DecryptButton" runat="server" Text="Decrypt" OnClick="DecryptButton_Click" />    
    <br />
    <asp:Label ID="CryptRes" runat="server" Text=""></asp:Label>

    <!-- Service 1 - Ethan Robinson -->
    <h4>Currency Converter Service</h4>

    <p>used currencyconverter api from apiLayer.com</p>
    <p>Methods:</p>
    <p>double Convert(string fromCurrency, string toCurrency, double fromCurrencyAmount)</p>
    <p>Dictionary(string, string) GetCountries()</p>
    <p>Input: two strings and a double </p>
    <p>Output: double value of converted currency.</p>
    <p>By: Ethan Robinson</p>

    <asp:Label ID="Label3" runat="server" Text="Input amount in your currency:"></asp:Label>
    <asp:TextBox ID="moneyFrom" runat="server"></asp:TextBox>
    <ajaxToolkit:ComboBox ID="cmbFrom" runat="server"></ajaxToolkit:ComboBox>
    <br />

    <asp:Label ID="Label4" runat="server" Text="Amount in desired currency:"></asp:Label>
    <asp:TextBox ID="moneyTo" runat="server"></asp:TextBox>
    <ajaxToolkit:ComboBox ID="cmbTo" runat="server"> </ajaxToolkit:ComboBox>
    <br />

    <asp:Button ID="Button1" runat="server" OnClick="Button1_Click" Text="Convert" />
     
    <!-- Service 2 - Ethan Robinson -->
    <h4>Text Translator Service</h4>

    <p>used text translator api from apiLayer.com</p>
    <p>Methods:</p>
    <p>string[] GetLanguages()</p>
    <p>string Translate(string target, string body);</p>
    <p>Input: two strings </p>
    <p>Output: string value of translated text.</p>
    <p>By: Ethan Robinson</p>

    <asp:Label ID="Label1" runat="server" Text="Text in prefered language:"></asp:Label>
    <asp:TextBox ID="TextBody" runat="server"></asp:TextBox><ajaxToolkit:ComboBox ID="cmbTextFrom" runat="server">
    </ajaxToolkit:ComboBox>
    <br />

    <asp:Label ID="Label2" runat="server" Text="Translated text:          "></asp:Label>
    <asp:TextBox ID="Translated" runat="server"></asp:TextBox>
    <br />

    <asp:Button ID="Button2" runat="server" OnClick="Button2_Click" Text="Translate" />
</asp:Content>
