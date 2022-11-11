<%@ Page Title="Project 4" Language="C#" MasterPageFile="~/Site.Master" AutoEventWireup="true" CodeBehind="Default.aspx.cs" Inherits="WebApp._Default" %>

<asp:Content ID="BodyContent" ContentPlaceHolderID="MainContent" runat="server">
    <h1>Verification</h1>
    <h6>Use to check if a xml and xsd file are verified.</h6>
    <p>URLs to use to test:</p>
    <p>XML: https://www.public.asu.edu/~tfichier/Cruises.xml</p>
    <p>XML (w/ error): https://www.public.asu.edu/~tfichier/CruisesError.xml</p>
    <p>XSD: https://www.public.asu.edu/~tfichier/Cruises.xsd</p>
    <asp:Label ID="Label1" runat="server" Text="XML Url:"></asp:Label>
    <asp:TextBox ID="xmlUrl" runat="server"></asp:TextBox>
    <br />
    <asp:Label ID="Label2" runat="server" Text="XSD Url:"></asp:Label>
    <asp:TextBox ID="xsdUrl" runat="server"></asp:TextBox>
    <br />
    <asp:Button ID="VerificationButton" runat="server" Text="Verify" OnClick="VerificationButton_Click" />
    <br />
    <asp:Label ID="VerificationInfo" runat="server" Text=""></asp:Label>

    <h1>Add Cruise</h1>
    <h6>Search XML file using link and xpath expression</h6>
    <p>Example for search can be "/Cruises/Cruise[1]/ParentCompany"</p>
    <asp:Label runat="server" Text="XML Url:"></asp:Label>
    <asp:TextBox ID="xmlUrl2" runat="server"></asp:TextBox>
    <br />
    <asp:Label runat="server" Text="Path Search Expression:"></asp:Label>
    <asp:TextBox ID="pathEx" runat="server"></asp:TextBox>
    <br />
    <asp:Button ID="SearchButton" runat="server" Text="Search" OnClick="SearchButton_Click" />
    <br />
    <asp:Label ID="SearchInfo" runat="server" Text=""></asp:Label>
</asp:Content>
