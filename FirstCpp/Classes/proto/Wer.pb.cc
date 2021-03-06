// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: Wer.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "Wer.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace {

const ::google::protobuf::Descriptor* WerTable_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  WerTable_reflection_ = NULL;
const ::google::protobuf::Descriptor* Wer_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  Wer_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_Wer_2eproto() {
  protobuf_AddDesc_Wer_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "Wer.proto");
  GOOGLE_CHECK(file != NULL);
  WerTable_descriptor_ = file->message_type(0);
  static const int WerTable_offsets_[2] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(WerTable, tname_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(WerTable, tlist_),
  };
  WerTable_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      WerTable_descriptor_,
      WerTable::default_instance_,
      WerTable_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(WerTable, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(WerTable, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(WerTable));
  Wer_descriptor_ = file->message_type(1);
  static const int Wer_offsets_[7] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Wer, id_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Wer, name_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Wer, teampoint_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Wer, point_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Wer, effect1_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Wer, effect2_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Wer, effect3_),
  };
  Wer_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      Wer_descriptor_,
      Wer::default_instance_,
      Wer_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Wer, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Wer, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(Wer));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_Wer_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    WerTable_descriptor_, &WerTable::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    Wer_descriptor_, &Wer::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_Wer_2eproto() {
  delete WerTable::default_instance_;
  delete WerTable_reflection_;
  delete Wer::default_instance_;
  delete Wer_reflection_;
}

void protobuf_AddDesc_Wer_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\tWer.proto\".\n\010WerTable\022\r\n\005tname\030\001 \001(\t\022\023"
    "\n\005tlist\030\002 \003(\0132\004.Wer\"t\n\003Wer\022\n\n\002id\030\001 \001(\005\022\014"
    "\n\004name\030\002 \001(\t\022\021\n\tteampoint\030\003 \001(\t\022\r\n\005point"
    "\030\004 \001(\005\022\017\n\007effect1\030\005 \001(\t\022\017\n\007effect2\030\006 \001(\t"
    "\022\017\n\007effect3\030\007 \001(\t", 177);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "Wer.proto", &protobuf_RegisterTypes);
  WerTable::default_instance_ = new WerTable();
  Wer::default_instance_ = new Wer();
  WerTable::default_instance_->InitAsDefaultInstance();
  Wer::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_Wer_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_Wer_2eproto {
  StaticDescriptorInitializer_Wer_2eproto() {
    protobuf_AddDesc_Wer_2eproto();
  }
} static_descriptor_initializer_Wer_2eproto_;

// ===================================================================

#ifndef _MSC_VER
const int WerTable::kTnameFieldNumber;
const int WerTable::kTlistFieldNumber;
#endif  // !_MSC_VER

WerTable::WerTable()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void WerTable::InitAsDefaultInstance() {
}

WerTable::WerTable(const WerTable& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void WerTable::SharedCtor() {
  _cached_size_ = 0;
  tname_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

WerTable::~WerTable() {
  SharedDtor();
}

void WerTable::SharedDtor() {
  if (tname_ != &::google::protobuf::internal::kEmptyString) {
    delete tname_;
  }
  if (this != default_instance_) {
  }
}

void WerTable::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* WerTable::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return WerTable_descriptor_;
}

const WerTable& WerTable::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_Wer_2eproto();
  return *default_instance_;
}

WerTable* WerTable::default_instance_ = NULL;

WerTable* WerTable::New() const {
  return new WerTable;
}

void WerTable::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (has_tname()) {
      if (tname_ != &::google::protobuf::internal::kEmptyString) {
        tname_->clear();
      }
    }
  }
  tlist_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool WerTable::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional string tname = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_tname()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8String(
            this->tname().data(), this->tname().length(),
            ::google::protobuf::internal::WireFormat::PARSE);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(18)) goto parse_tlist;
        break;
      }

      // repeated .Wer tlist = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_tlist:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                input, add_tlist()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(18)) goto parse_tlist;
        if (input->ExpectAtEnd()) return true;
        break;
      }

      default: {
      handle_uninterpreted:
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          return true;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
  return true;
#undef DO_
}

void WerTable::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // optional string tname = 1;
  if (has_tname()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->tname().data(), this->tname().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      1, this->tname(), output);
  }

  // repeated .Wer tlist = 2;
  for (int i = 0; i < this->tlist_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      2, this->tlist(i), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* WerTable::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // optional string tname = 1;
  if (has_tname()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->tname().data(), this->tname().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        1, this->tname(), target);
  }

  // repeated .Wer tlist = 2;
  for (int i = 0; i < this->tlist_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        2, this->tlist(i), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int WerTable::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional string tname = 1;
    if (has_tname()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->tname());
    }

  }
  // repeated .Wer tlist = 2;
  total_size += 1 * this->tlist_size();
  for (int i = 0; i < this->tlist_size(); i++) {
    total_size +=
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        this->tlist(i));
  }

  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void WerTable::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const WerTable* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const WerTable*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void WerTable::MergeFrom(const WerTable& from) {
  GOOGLE_CHECK_NE(&from, this);
  tlist_.MergeFrom(from.tlist_);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_tname()) {
      set_tname(from.tname());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void WerTable::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void WerTable::CopyFrom(const WerTable& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool WerTable::IsInitialized() const {

  return true;
}

void WerTable::Swap(WerTable* other) {
  if (other != this) {
    std::swap(tname_, other->tname_);
    tlist_.Swap(&other->tlist_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata WerTable::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = WerTable_descriptor_;
  metadata.reflection = WerTable_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int Wer::kIdFieldNumber;
const int Wer::kNameFieldNumber;
const int Wer::kTeampointFieldNumber;
const int Wer::kPointFieldNumber;
const int Wer::kEffect1FieldNumber;
const int Wer::kEffect2FieldNumber;
const int Wer::kEffect3FieldNumber;
#endif  // !_MSC_VER

Wer::Wer()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void Wer::InitAsDefaultInstance() {
}

Wer::Wer(const Wer& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void Wer::SharedCtor() {
  _cached_size_ = 0;
  id_ = 0;
  name_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  teampoint_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  point_ = 0;
  effect1_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  effect2_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  effect3_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Wer::~Wer() {
  SharedDtor();
}

void Wer::SharedDtor() {
  if (name_ != &::google::protobuf::internal::kEmptyString) {
    delete name_;
  }
  if (teampoint_ != &::google::protobuf::internal::kEmptyString) {
    delete teampoint_;
  }
  if (effect1_ != &::google::protobuf::internal::kEmptyString) {
    delete effect1_;
  }
  if (effect2_ != &::google::protobuf::internal::kEmptyString) {
    delete effect2_;
  }
  if (effect3_ != &::google::protobuf::internal::kEmptyString) {
    delete effect3_;
  }
  if (this != default_instance_) {
  }
}

void Wer::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Wer::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return Wer_descriptor_;
}

const Wer& Wer::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_Wer_2eproto();
  return *default_instance_;
}

Wer* Wer::default_instance_ = NULL;

Wer* Wer::New() const {
  return new Wer;
}

void Wer::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    id_ = 0;
    if (has_name()) {
      if (name_ != &::google::protobuf::internal::kEmptyString) {
        name_->clear();
      }
    }
    if (has_teampoint()) {
      if (teampoint_ != &::google::protobuf::internal::kEmptyString) {
        teampoint_->clear();
      }
    }
    point_ = 0;
    if (has_effect1()) {
      if (effect1_ != &::google::protobuf::internal::kEmptyString) {
        effect1_->clear();
      }
    }
    if (has_effect2()) {
      if (effect2_ != &::google::protobuf::internal::kEmptyString) {
        effect2_->clear();
      }
    }
    if (has_effect3()) {
      if (effect3_ != &::google::protobuf::internal::kEmptyString) {
        effect3_->clear();
      }
    }
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool Wer::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional int32 id = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &id_)));
          set_has_id();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(18)) goto parse_name;
        break;
      }

      // optional string name = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_name:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_name()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8String(
            this->name().data(), this->name().length(),
            ::google::protobuf::internal::WireFormat::PARSE);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(26)) goto parse_teampoint;
        break;
      }

      // optional string teampoint = 3;
      case 3: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_teampoint:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_teampoint()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8String(
            this->teampoint().data(), this->teampoint().length(),
            ::google::protobuf::internal::WireFormat::PARSE);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(32)) goto parse_point;
        break;
      }

      // optional int32 point = 4;
      case 4: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_point:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &point_)));
          set_has_point();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(42)) goto parse_effect1;
        break;
      }

      // optional string effect1 = 5;
      case 5: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_effect1:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_effect1()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8String(
            this->effect1().data(), this->effect1().length(),
            ::google::protobuf::internal::WireFormat::PARSE);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(50)) goto parse_effect2;
        break;
      }

      // optional string effect2 = 6;
      case 6: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_effect2:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_effect2()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8String(
            this->effect2().data(), this->effect2().length(),
            ::google::protobuf::internal::WireFormat::PARSE);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(58)) goto parse_effect3;
        break;
      }

      // optional string effect3 = 7;
      case 7: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_effect3:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_effect3()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8String(
            this->effect3().data(), this->effect3().length(),
            ::google::protobuf::internal::WireFormat::PARSE);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectAtEnd()) return true;
        break;
      }

      default: {
      handle_uninterpreted:
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          return true;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
  return true;
#undef DO_
}

void Wer::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // optional int32 id = 1;
  if (has_id()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(1, this->id(), output);
  }

  // optional string name = 2;
  if (has_name()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->name().data(), this->name().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      2, this->name(), output);
  }

  // optional string teampoint = 3;
  if (has_teampoint()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->teampoint().data(), this->teampoint().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      3, this->teampoint(), output);
  }

  // optional int32 point = 4;
  if (has_point()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(4, this->point(), output);
  }

  // optional string effect1 = 5;
  if (has_effect1()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->effect1().data(), this->effect1().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      5, this->effect1(), output);
  }

  // optional string effect2 = 6;
  if (has_effect2()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->effect2().data(), this->effect2().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      6, this->effect2(), output);
  }

  // optional string effect3 = 7;
  if (has_effect3()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->effect3().data(), this->effect3().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      7, this->effect3(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* Wer::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // optional int32 id = 1;
  if (has_id()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(1, this->id(), target);
  }

  // optional string name = 2;
  if (has_name()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->name().data(), this->name().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        2, this->name(), target);
  }

  // optional string teampoint = 3;
  if (has_teampoint()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->teampoint().data(), this->teampoint().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        3, this->teampoint(), target);
  }

  // optional int32 point = 4;
  if (has_point()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(4, this->point(), target);
  }

  // optional string effect1 = 5;
  if (has_effect1()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->effect1().data(), this->effect1().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        5, this->effect1(), target);
  }

  // optional string effect2 = 6;
  if (has_effect2()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->effect2().data(), this->effect2().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        6, this->effect2(), target);
  }

  // optional string effect3 = 7;
  if (has_effect3()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->effect3().data(), this->effect3().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        7, this->effect3(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int Wer::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional int32 id = 1;
    if (has_id()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->id());
    }

    // optional string name = 2;
    if (has_name()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->name());
    }

    // optional string teampoint = 3;
    if (has_teampoint()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->teampoint());
    }

    // optional int32 point = 4;
    if (has_point()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->point());
    }

    // optional string effect1 = 5;
    if (has_effect1()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->effect1());
    }

    // optional string effect2 = 6;
    if (has_effect2()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->effect2());
    }

    // optional string effect3 = 7;
    if (has_effect3()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->effect3());
    }

  }
  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void Wer::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const Wer* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const Wer*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void Wer::MergeFrom(const Wer& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_id()) {
      set_id(from.id());
    }
    if (from.has_name()) {
      set_name(from.name());
    }
    if (from.has_teampoint()) {
      set_teampoint(from.teampoint());
    }
    if (from.has_point()) {
      set_point(from.point());
    }
    if (from.has_effect1()) {
      set_effect1(from.effect1());
    }
    if (from.has_effect2()) {
      set_effect2(from.effect2());
    }
    if (from.has_effect3()) {
      set_effect3(from.effect3());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void Wer::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Wer::CopyFrom(const Wer& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Wer::IsInitialized() const {

  return true;
}

void Wer::Swap(Wer* other) {
  if (other != this) {
    std::swap(id_, other->id_);
    std::swap(name_, other->name_);
    std::swap(teampoint_, other->teampoint_);
    std::swap(point_, other->point_);
    std::swap(effect1_, other->effect1_);
    std::swap(effect2_, other->effect2_);
    std::swap(effect3_, other->effect3_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata Wer::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = Wer_descriptor_;
  metadata.reflection = Wer_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

// @@protoc_insertion_point(global_scope)
