#pragma once
#include <string>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/sax/Locator.hpp>
#include <xercesc/sax2/Attributes.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>
#include <xercesc/util/PlatformUtils.hpp>
#include <cassert>
#include <sstream>
#include <cstdlib>
#include <iostream>

#include "Configuration.hh"

using namespace xercesc;

/*!
 * \brief Implementuje reakcje na napotkane elementu opisu akcji
 *
 * Klasa zawiera zestaw metod, które wywoływane są w trakcie czytania i analizy
 * pliku XML.
 */
class XMLInterp4Config : public xercesc::DefaultHandler
{
public:
  /*!
    * \brief Inicjalizuje obiekt i kojarzy go z listą poleceń robota
    */
  XMLInterp4Config(Configuration &rConfig);

  /*!
    * \brief Wywoływana jest na początku dokumentu
    */
  virtual void startDocument() override;
  /*!
    * \brief Wywoływana jest na końcu dokumentu
    */
  virtual void endDocument() override;

  /*!
    * \brief Wywoływana jest po napotkaniu nowego elementu XML
    */
  virtual void startElement(
      const XMLCh *const pURI,
      const XMLCh *const pLocalName,
      const XMLCh *const pQNname,
      const xercesc::Attributes &attrs) override;

  /*!
    * \brief Wywoływana jest po dojściu do końca elementu XML
    */
  virtual void endElement(
      const XMLCh *const pURI,
      const XMLCh *const pLocalName,
      const XMLCh *const pQNname) override;
  /*!
    * \brief Wywoływana jest gdy napotkany zostanie błąd fatalny
    */
  void fatalError(const xercesc::SAXParseException &);
  /*!
    * \brief Wywoływana jest gdy napotkany zostanie błąd
    */
  void error(const xercesc::SAXParseException &exc);
  /*!
    * \brief Wywoływana jest gdy parser sygnalizuje ostrzeżenie
    */
  void warning(const xercesc::SAXParseException &exc);

  /*!
     * \brief Wykonuje operacje związane z danym elementem XML
     */
  void WhenStartElement(const std::string &ElemName,
                        const xercesc::Attributes &Attrs);
  /*!
     * \brief Analizuje atrybuty i  odpwiednio je interpretuje
     */
  void ProcessLibAttrs(const xercesc::Attributes &Attrs);
  /*!
     * \brief Analizuje atrybuty i odpwiednio je interpretuje
     */
  void ProcessCubeAttrs(const xercesc::Attributes &Attrs);

private:
  Configuration &config;
};

bool ReadFile(const char *sFileName, Configuration &rConfig);
