using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace WebApplication
{
    // member page handler
    public partial class Member : Page
    {
        private string[] countries;
        private string[] countryRate;

        //private string[] languages;
        private string[] languageName;

        // handle the page load and add some elements to html from remote services
        protected void Page_Load(object sender, EventArgs e)
        {
            //Response.Write("number of Users Online = " + Application["numofusers"].ToString());
            CurrencyService.Service1Client currencyConvert = new CurrencyService.Service1Client();
            TranslatorService.Service1Client textTranslate = new TranslatorService.Service1Client();

            Dictionary<string, string> symbolData = currencyConvert.GetCountries();
            string[] languageData = textTranslate.GetLanguages();

            //languages = new string[languageData.Count];
            //languageData.Values.CopyTo(languages, 0);

            languageName = new string[languageData.Length];
            languageData.CopyTo(languageName, 0);

            countries = new string[symbolData.Count];
            symbolData.Values.CopyTo(countries, 0);

            countryRate = new string[symbolData.Count];
            symbolData.Keys.CopyTo(countryRate, 0);

            if (cmbFrom.Items.Count == 0 && cmbTextFrom.Items.Count == 0)
            {

                for (int i = 0; i < countries.Length; i++)
                {
                    cmbFrom.Items.Add(countries[i]);
                    cmbTo.Items.Add(countries[i]);
                }
                for (int j = 0; j < languageData.Length; j++)
                {
                    cmbTextFrom.Items.Add(languageData[j]);
                }
            }
        }

        // handle currency converter button
        protected void Button1_Click(object sender, EventArgs e)
        {
            CurrencyService.Service1Client currencyConvert = new CurrencyService.Service1Client();
            string fromCurrencySymbol = countryRate[cmbFrom.SelectedIndex];
            string toCurrencySymbol = countryRate[cmbTo.SelectedIndex];
            double currencyAmount = double.Parse(moneyFrom.Text);
            double finalValue = currencyConvert.Convert(fromCurrencySymbol, toCurrencySymbol, currencyAmount);
            finalValue = Math.Round(finalValue, 2);
            moneyTo.Text = finalValue.ToString();
        }

        // handle translate service button
        protected void Button2_Click(object sender, EventArgs e)
        {
            TranslatorService.Service1Client textTranslate = new TranslatorService.Service1Client();
            string body = TextBody.Text;
            string target = languageName[cmbTextFrom.SelectedIndex];
            string finalText = textTranslate.Translate(target, body);
            Translated.Text = finalText;
        }

        // handle encrypt button and ref dll
        protected void EncryptButton_Click(object sender, EventArgs e)
        {
            if (RawInput.Text != "")
            {
                string x = Crypt.Crypt.Encrypt(RawInput.Text);
                CryptRes.Text = x;
            }
        }

        // handle decrypt button and ref dll
        protected void DecryptButton_Click(object sender, EventArgs e)
        {
            if (RawInput.Text != "")
            {
                string x = Crypt.Crypt.Decrypt(RawInput.Text);
                CryptRes.Text = x;
            }
        }
    }
}