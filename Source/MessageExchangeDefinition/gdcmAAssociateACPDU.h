/*=========================================================================
 *
 *  Copyright Insight Software Consortium
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/

#ifndef GDCMAASSOCIATEACPDU_H
#define GDCMAASSOCIATEACPDU_H

#include "gdcmTypes.h"
#include "gdcmApplicationContext.h"
#include "gdcmPresentationContextAC.h"
#include "gdcmUserInformation.h"
#include "gdcmBasePDU.h"

namespace gdcm
{

// TODO: MM : does swig handle nested namespace
// I would like to avoid polluting gdcm namespace with such low level details the networ
// primitives:
namespace network
{
class AAssociateRQPDU;

/**
Table 9-17
ASSOCIATE-AC PDU fields
 */
class GDCM_EXPORT AAssociateACPDU : public BasePDU
{
public:
  AAssociateACPDU();
  std::istream &Read(std::istream &is);
  const std::ostream &Write(std::ostream &os) const;

  void AddPresentationContextAC( PresentationContextAC const &pcac );

  const PresentationContextAC &GetPresentationContextAC( unsigned int i ) {
    assert( !PresContextAC.empty() && i < PresContextAC.size() );
    return PresContextAC[i];
  }
  typedef std::vector<PresentationContextAC>::size_type SizeType;
  SizeType GetNumberOfPresentationContextAC() const {
    return PresContextAC.size();
  }

  size_t Size() const;

  void Print(std::ostream &os) const;
  bool IsLastFragment() const { return true; }

  void InitSimple( AAssociateRQPDU const & rqpdu );

  void SetCalledAETitle(const char calledaetitle[16]);
  const char *GetCalledAETitle() const { return CalledAETitle; }
  void SetCallingAETitle(const char callingaetitle[16]);
  const char *GetCallingAETitle() const { return CallingAETitle; }

private:
  static const uint8_t ItemType; // PDUType ?
  static const uint8_t Reserved2;
  uint32_t PDULength; // len of
  static const uint16_t ProtocolVersion;
  static const uint16_t Reserved9_10;
  static const uint8_t CalledAETitle[16];
  static const uint8_t CallingAETitle[16];
  static const uint8_t Reserved43_74[32];
  /*
  75-xxx Variable items This variable field shall contain the following items: one Application
  Context Item, one or more Presentation Context Item(s) and one User
  Information Item. For a complete description of these items see Sections
  7.1.1.2, 7.1.1.14, and 7.1.1.6.
   */
  ApplicationContext AppContext;
  std::vector<PresentationContextAC>	PresContextAC;
  UserInformation UserInfo;
};

} // end namespace network

} // end namespace gdcm

#endif //GDCMAASSOCIATEACPDU_H
