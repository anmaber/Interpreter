#include "xmlinterp.hh"

/*!
 * Konstruktor klasy. Tutaj należy zainicjalizować wszystkie
 * dodatkowe pola.
 */
XMLInterp4Config::XMLInterp4Config(Configuration &rConfig)
    : config(rConfig)
{
}

/*!
 * Metoda wywoływana jest bezpośrednio przed rozpoczęciem
 * przetwarzana dokumentu XML.
 */
void XMLInterp4Config::startDocument()
{
  std::cout << "*** Rozpoczecie przetwarzania dokumentu XML." << std::endl;
}

/*!
 * Metoda wywoływana jest bezpośrednio po zakończeniu
 * przetwarzana dokumentu XML.
 */
void XMLInterp4Config::endDocument()
{
  std::cout << "=== Koniec przetwarzania dokumentu XML." << std::endl;
}

/*!
 * Analizuje atrybuty elementu XML \p "Lib" i odpowiednio je interpretuje.
 * \param[in] Attrs - (\b in) atrybuty elementu XML \p "Lib".
 */
void XMLInterp4Config::ProcessLibAttrs(const xercesc::Attributes &Attrs)
{
  if (Attrs.getLength() != 1)
  {
    std::cerr << "Zla ilosc atrybutow dla \"Lib\"" << std::endl;
    exit(1);
  }

  char *sParamName = xercesc::XMLString::transcode(Attrs.getQName(0));

  if (strcmp(sParamName, "Name"))
  {
    std::cerr << "Zla nazwa atrybutu dla Lib" << std::endl;
    exit(1);
  }

  XMLSize_t Size = 0;
  char *sLibName = xercesc::XMLString::transcode(Attrs.getValue(Size));

  std::cout << "  Nazwa biblioteki: " << sLibName << std::endl;
  //TO DO: przenies caly fragment do config
  config.libsConfiguration.push_back(sLibName);

  xercesc::XMLString::release(&sParamName);
  xercesc::XMLString::release(&sLibName);
}

/*!
 * Analizuje atrybuty. Sprawdza czy ich nazwy są poprawne. Jeśli tak,
 * to pobiera wartości atrybutów (w postaci napisów) i przekazuje ...
 * \param[in] Attrs - (\b we,) atrybuty elementu XML \p "Cybe".
 */
void XMLInterp4Config::ProcessCubeAttrs(const xercesc::Attributes &Attrs)
{
  if (Attrs.getLength() != 3)
  {
    std::cerr << "Zla ilosc atrybutow dla \"Cube\"" << std::endl;
    exit(1);
  }

  /*
  *  Tutaj pobierane sa nazwy pierwszego i drugiego atrybuty.
  *  Sprawdzamy, czy na pewno jest to Name i Value.
  */

  char *sName_Name = xercesc::XMLString::transcode(Attrs.getQName(0));
  char *sName_SizeXYZ = xercesc::XMLString::transcode(Attrs.getQName(1));
  char *sName_RGB = xercesc::XMLString::transcode(Attrs.getQName(2));

  XMLSize_t Index = 0;
  char *sValue_Name = xercesc::XMLString::transcode(Attrs.getValue(Index));
  char *sValue_SizeXYZ = xercesc::XMLString::transcode(Attrs.getValue(1));
  char *sValue_RGB = xercesc::XMLString::transcode(Attrs.getValue(2));

  //------------------------------------------------
  // Wyświetlenie nazw atrybutów i ich "wartości"
  //
  std::cout << " Atrybuty:" << std::endl
            << "     " << sName_Name << " = \"" << sValue_Name << "\"" << std::endl
            << "     " << sName_SizeXYZ << " = \"" << sValue_SizeXYZ << "\"" << std::endl
            << "     " << sName_RGB << " = \"" << sValue_RGB << "\"" << std::endl
            << std::endl;
  //------------------------------------------------
  // Przykład czytania wartości parametrów
  //
  std::istringstream IStrm;
  IStrm.str(sValue_SizeXYZ);
  double x, y, z;

  IStrm >> x >> y >> z;
  if (IStrm.fail())
  {
    std::cerr << " Blad!!!" << std::endl;
  }
  else
  {
    std::cout << " Czytanie wartosci OK!!!" << std::endl;
    std::cout << "     " << x << "  " << y << "  " << z << std::endl;
  }
  //TO DO: przenies caly fragment do config
  config.sceneConfiguration.push_back({sValue_Name, sValue_SizeXYZ, sValue_RGB});
  
  xercesc::XMLString::release(&sName_Name);
  xercesc::XMLString::release(&sName_SizeXYZ);
  xercesc::XMLString::release(&sName_RGB);
  xercesc::XMLString::release(&sValue_Name);
  xercesc::XMLString::release(&sValue_SizeXYZ);
  xercesc::XMLString::release(&sValue_RGB);
}

/*!
 * Wykonuje operacje związane z wystąpieniem danego elementu XML.
 * W przypadku elementu \p "Action" będzie to utworzenie obiektu
 * reprezentującego odpowiednią działanie robota.
 * W przypadku elementu \p "Parameter" będzie to zapisanie parametrów
 * związanych z danym działaniem.
 * \param[in] ElemName -
 * \param[in] Attrs - (\b we,) atrybuty napotkanego elementu XML.
 */
void XMLInterp4Config::WhenStartElement(const std::string &ElemName,
                                        const xercesc::Attributes &Attrs)
{
  if (ElemName == "Lib")
  {
    ProcessLibAttrs(Attrs);
    return;
  }

  if (ElemName == "Cube")
  {
    ProcessCubeAttrs(Attrs);
    return;
  }
}

/*!
 * Metoda jest wywoływana po napotkaniu nowego elementu XML, np.
 * gdy zostanie napotkany element:
   \verbatim
     <Action Name="Rotate">
   \endverbatim
 *  to poprzez parametr \e xscElemName jest dostęp do nazwy elementu
 *  tzn. \p Action, 
 *  \param[in] pLocalName -  umożliwia dostęp do nazwy elementu XML.
 *                 W podanym przykładzie nazwą elementu XML jest "Action".
 *  \param[in] Attrs -  lista atrybutów danego symbolu XML.
 *                 W przykładzie pokazanym powyżej listę atrybutów
 *                 będą stanowiły napisy:
 */
/*
 * Te metode nalezy odpowiednio zdekomponowac!!!
 */
void XMLInterp4Config::startElement(const XMLCh *const pURI,
                                    const XMLCh *const pLocalName,
                                    const XMLCh *const pQNname,
                                    const xercesc::Attributes &Attrs)
{
  char *sElemName = xercesc::XMLString::transcode(pLocalName);
  std::cout << "+++ Poczatek elementu: " << sElemName << std::endl;

  WhenStartElement(sElemName, Attrs);

  xercesc::XMLString::release(&sElemName);
}

/*!
 * Metoda zostaje wywołana w momencie zakończenia danego elementu
 * XML, np. jeżeli w pliku jest wpis:
   \verbatim
     <Lib Name="Rotate">
     </Lib>
   \endverbatim
 * to metoda ta zostanie wywołana po napotkaniu znacznika
 * \p </Lib>. Jeżeli element XML ma formę skróconą, tzn.
   \verbatim
     <Parametr Name="Rotate"/>
   \endverbatim
 * to wówczas wywołana metoda wywołana zostanie w momencie
 * napotkania sekwencji "/>"
 *  \param[in] pLocalName -  umożliwia dostęp do nazwy elementu XML.
 *                 W podanym przykładzie nazwą elementu XML jest "Lib".
 */
void XMLInterp4Config::endElement(const XMLCh *const pURI,
                                  const XMLCh *const pLocalName,
                                  const XMLCh *const pQName)
{
  char *sElemName = xercesc::XMLString::transcode(pLocalName);
  std::cout << "----- Koniec elementu: " << sElemName << std::endl;

  xercesc::XMLString::release(&sElemName);
}

/*!
 * Metoda wywoływana jest, gdy napotkany zostanie błąd fatalny,
 * np.
  \verbatim
    <Action Name="Rotate">
    </Parametr>
  \endverbatim
 */
void XMLInterp4Config::fatalError(const xercesc::SAXParseException &Exception)
{
  char *sMessage = xercesc::XMLString::transcode(Exception.getMessage());
  char *sSystemId = xercesc::XMLString::transcode(Exception.getSystemId());

  std::cerr << "Blad fatalny! " << std::endl
            << "    Plik:  " << sSystemId << std::endl
            << "   Linia: " << Exception.getLineNumber() << std::endl
            << " Kolumna: " << Exception.getColumnNumber() << std::endl
            << " Informacja: " << sMessage
            << std::endl;

  xercesc::XMLString::release(&sMessage);
  xercesc::XMLString::release(&sSystemId);
}

/*!
 * Metoda jest wywoływana, gdy napotkany zostanie błąd, który nie
 * jest traktowany jako fatalny. W ten sposób traktowane są błędy
 * występujące w opisie gramatyki dokumentu.
 * \param[in] Except - zawiera informacje dotyczące błędu. Informacje
 *                     te to opis błędu oraz numer linii, w której
 *                     wystąpił błąd.
 */
void XMLInterp4Config::error(const xercesc::SAXParseException &Exception)
{
  std::cerr << "Blad ..." << std::endl;

  /*
   * Tutaj należy wstawić odpowiedni kod. Tekst wyświetlany powyżej
   * jest tylko "atrapą".
   */
}

/*!
 *
 */
void XMLInterp4Config::warning(const xercesc::SAXParseException &Exception)
{
  std::cerr << "Ostrzezenie ..." << std::endl;

  /*
   * Tutaj należy wstawić odpowiedni kod. Tekst wyświetlany powyżej
   * jest tylko "atrapą".
   */
}

bool ReadFile(const char *sFileName, Configuration &rConfig)
{
  try
  {
    XMLPlatformUtils::Initialize();
  }
  catch (const XMLException &toCatch)
  {
    char *message = XMLString::transcode(toCatch.getMessage());
    std::cerr << "Error during initialization! :\n";
    std::cerr << "Exception message is: \n"
              << message << "\n";
    XMLString::release(&message);
    return 1;
  }

  SAX2XMLReader *pParser = XMLReaderFactory::createXMLReader();

  pParser->setFeature(XMLUni::fgSAX2CoreNameSpaces, true);
  pParser->setFeature(XMLUni::fgSAX2CoreValidation, true);
  pParser->setFeature(XMLUni::fgXercesDynamic, false);
  pParser->setFeature(XMLUni::fgXercesSchema, true);
  pParser->setFeature(XMLUni::fgXercesSchemaFullChecking, true);

  pParser->setFeature(XMLUni::fgXercesValidationErrorAsFatal, true);

  DefaultHandler *pHandler = new XMLInterp4Config(rConfig);
  pParser->setContentHandler(pHandler);
  pParser->setErrorHandler(pHandler);

  try
  {

    if (!pParser->loadGrammar("../config/config.xsd",
                              xercesc::Grammar::SchemaGrammarType, true))
    {
      std::cerr << "!!! Plik grammar/actions.xsd, '" << std::endl
                << "!!! ktory zawiera opis gramatyki, nie moze zostac wczytany."
                << std::endl;
      return false;
    }
    pParser->setFeature(XMLUni::fgXercesUseCachedGrammarInParse, true);
    pParser->parse(sFileName);
  }
  catch (const XMLException &Exception)
  {
    char *sMessage = XMLString::transcode(Exception.getMessage());
    std::cerr << "Informacja o wyjatku: \n"
              << "   " << sMessage << "\n";
    XMLString::release(&sMessage);
    return false;
  }
  catch (const SAXParseException &Exception)
  {
    char *sMessage = XMLString::transcode(Exception.getMessage());
    char *sSystemId = xercesc::XMLString::transcode(Exception.getSystemId());

    std::cerr << "Blad! " << std::endl
              << "    Plik:  " << sSystemId << std::endl
              << "   Linia: " << Exception.getLineNumber() << std::endl
              << " Kolumna: " << Exception.getColumnNumber() << std::endl
              << " Informacja: " << sMessage
              << std::endl;

    XMLString::release(&sMessage);
    XMLString::release(&sSystemId);
    return false;
  }
  catch (...)
  {
    std::cout << "Zgloszony zostal nieoczekiwany wyjatek!\n";
    return false;
  }

  delete pParser;
  delete pHandler;
  return true;
}