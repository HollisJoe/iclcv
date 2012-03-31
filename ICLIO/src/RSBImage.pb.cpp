// Generated by the protocol buffer compiler.  DO NOT EDIT!

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include <ICLIO/RSBImage.pb.h>

#include <algorithm>

#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace icl {

namespace {

const ::google::protobuf::Descriptor* RSBImage_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  RSBImage_reflection_ = NULL;
const ::google::protobuf::EnumDescriptor* RSBImage_Format_descriptor_ = NULL;

}  // namespace


void protobuf_AssignDesc_RSBImage_2eproto() {
  protobuf_AddDesc_RSBImage_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "RSBImage.proto");
  GOOGLE_CHECK(file != NULL);
  RSBImage_descriptor_ = file->message_type(0);
  static const int RSBImage_offsets_[13] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(RSBImage, width_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(RSBImage, height_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(RSBImage, channels_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(RSBImage, roix_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(RSBImage, roiy_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(RSBImage, roiw_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(RSBImage, roih_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(RSBImage, format_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(RSBImage, time_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(RSBImage, compressionmode_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(RSBImage, compressionquality_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(RSBImage, data_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(RSBImage, metadata_),
  };
  RSBImage_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      RSBImage_descriptor_,
      RSBImage::default_instance_,
      RSBImage_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(RSBImage, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(RSBImage, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(RSBImage));
  RSBImage_Format_descriptor_ = RSBImage_descriptor_->enum_type(0);
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_RSBImage_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    RSBImage_descriptor_, &RSBImage::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_RSBImage_2eproto() {
  delete RSBImage::default_instance_;
  delete RSBImage_reflection_;
}

void protobuf_AddDesc_RSBImage_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\016RSBImage.proto\022\003icl\"\366\002\n\010RSBImage\022\r\n\005wi"
    "dth\030\001 \002(\r\022\016\n\006height\030\002 \002(\r\022\020\n\010channels\030\003 "
    "\002(\r\022\014\n\004roix\030\004 \002(\r\022\014\n\004roiy\030\005 \002(\r\022\014\n\004roiw\030"
    "\006 \002(\r\022\014\n\004roih\030\007 \002(\r\022$\n\006format\030\010 \002(\0162\024.ic"
    "l.RSBImage.Format\022\014\n\004time\030\t \002(\003\022\027\n\017compr"
    "essionMode\030\n \002(\t\022\032\n\022compressionQuality\030\013"
    " \002(\t\022\014\n\004data\030\014 \002(\014\022\020\n\010metadata\030\r \001(\t\"x\n\006"
    "Format\022\016\n\nformatGray\020\000\022\r\n\tformatRGB\020\001\022\r\n"
    "\tformatHLS\020\002\022\r\n\tformatYUV\020\003\022\r\n\tformatLAB"
    "\020\004\022\020\n\014formatChroma\020\005\022\020\n\014formatMatrix\020\006", 398);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "RSBImage.proto", &protobuf_RegisterTypes);
  RSBImage::default_instance_ = new RSBImage();
  RSBImage::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_RSBImage_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_RSBImage_2eproto {
  StaticDescriptorInitializer_RSBImage_2eproto() {
    protobuf_AddDesc_RSBImage_2eproto();
  }
} static_descriptor_initializer_RSBImage_2eproto_;


// ===================================================================

const ::google::protobuf::EnumDescriptor* RSBImage_Format_descriptor() {
  protobuf_AssignDescriptorsOnce();
  return RSBImage_Format_descriptor_;
}
bool RSBImage_Format_IsValid(int value) {
  switch(value) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
      return true;
    default:
      return false;
  }
}

#ifndef _MSC_VER
const RSBImage_Format RSBImage::formatGray;
const RSBImage_Format RSBImage::formatRGB;
const RSBImage_Format RSBImage::formatHLS;
const RSBImage_Format RSBImage::formatYUV;
const RSBImage_Format RSBImage::formatLAB;
const RSBImage_Format RSBImage::formatChroma;
const RSBImage_Format RSBImage::formatMatrix;
const RSBImage_Format RSBImage::Format_MIN;
const RSBImage_Format RSBImage::Format_MAX;
const int RSBImage::Format_ARRAYSIZE;
#endif  // _MSC_VER
#ifndef _MSC_VER
const int RSBImage::kWidthFieldNumber;
const int RSBImage::kHeightFieldNumber;
const int RSBImage::kChannelsFieldNumber;
const int RSBImage::kRoixFieldNumber;
const int RSBImage::kRoiyFieldNumber;
const int RSBImage::kRoiwFieldNumber;
const int RSBImage::kRoihFieldNumber;
const int RSBImage::kFormatFieldNumber;
const int RSBImage::kTimeFieldNumber;
const int RSBImage::kCompressionModeFieldNumber;
const int RSBImage::kCompressionQualityFieldNumber;
const int RSBImage::kDataFieldNumber;
const int RSBImage::kMetadataFieldNumber;
#endif  // !_MSC_VER

RSBImage::RSBImage()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void RSBImage::InitAsDefaultInstance() {
}

RSBImage::RSBImage(const RSBImage& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void RSBImage::SharedCtor() {
  _cached_size_ = 0;
  width_ = 0u;
  height_ = 0u;
  channels_ = 0u;
  roix_ = 0u;
  roiy_ = 0u;
  roiw_ = 0u;
  roih_ = 0u;
  format_ = 0;
  time_ = GOOGLE_LONGLONG(0);
  compressionmode_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  compressionquality_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  data_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  metadata_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

RSBImage::~RSBImage() {
  SharedDtor();
}

void RSBImage::SharedDtor() {
  if (compressionmode_ != &::google::protobuf::internal::kEmptyString) {
    delete compressionmode_;
  }
  if (compressionquality_ != &::google::protobuf::internal::kEmptyString) {
    delete compressionquality_;
  }
  if (data_ != &::google::protobuf::internal::kEmptyString) {
    delete data_;
  }
  if (metadata_ != &::google::protobuf::internal::kEmptyString) {
    delete metadata_;
  }
  if (this != default_instance_) {
  }
}

void RSBImage::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* RSBImage::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return RSBImage_descriptor_;
}

const RSBImage& RSBImage::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_RSBImage_2eproto();  return *default_instance_;
}

RSBImage* RSBImage::default_instance_ = NULL;

RSBImage* RSBImage::New() const {
  return new RSBImage;
}

void RSBImage::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    width_ = 0u;
    height_ = 0u;
    channels_ = 0u;
    roix_ = 0u;
    roiy_ = 0u;
    roiw_ = 0u;
    roih_ = 0u;
    format_ = 0;
  }
  if (_has_bits_[8 / 32] & (0xffu << (8 % 32))) {
    time_ = GOOGLE_LONGLONG(0);
    if (has_compressionmode()) {
      if (compressionmode_ != &::google::protobuf::internal::kEmptyString) {
        compressionmode_->clear();
      }
    }
    if (has_compressionquality()) {
      if (compressionquality_ != &::google::protobuf::internal::kEmptyString) {
        compressionquality_->clear();
      }
    }
    if (has_data()) {
      if (data_ != &::google::protobuf::internal::kEmptyString) {
        data_->clear();
      }
    }
    if (has_metadata()) {
      if (metadata_ != &::google::protobuf::internal::kEmptyString) {
        metadata_->clear();
      }
    }
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool RSBImage::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required uint32 width = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &width_)));
          set_has_width();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(16)) goto parse_height;
        break;
      }
      
      // required uint32 height = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_height:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &height_)));
          set_has_height();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(24)) goto parse_channels;
        break;
      }
      
      // required uint32 channels = 3;
      case 3: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_channels:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &channels_)));
          set_has_channels();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(32)) goto parse_roix;
        break;
      }
      
      // required uint32 roix = 4;
      case 4: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_roix:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &roix_)));
          set_has_roix();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(40)) goto parse_roiy;
        break;
      }
      
      // required uint32 roiy = 5;
      case 5: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_roiy:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &roiy_)));
          set_has_roiy();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(48)) goto parse_roiw;
        break;
      }
      
      // required uint32 roiw = 6;
      case 6: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_roiw:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &roiw_)));
          set_has_roiw();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(56)) goto parse_roih;
        break;
      }
      
      // required uint32 roih = 7;
      case 7: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_roih:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &roih_)));
          set_has_roih();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(64)) goto parse_format;
        break;
      }
      
      // required .icl.RSBImage.Format format = 8;
      case 8: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_format:
          int value;
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   int, ::google::protobuf::internal::WireFormatLite::TYPE_ENUM>(
                 input, &value)));
          if (::icl::RSBImage_Format_IsValid(value)) {
            set_format(static_cast< ::icl::RSBImage_Format >(value));
          } else {
            mutable_unknown_fields()->AddVarint(8, value);
          }
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(72)) goto parse_time;
        break;
      }
      
      // required int64 time = 9;
      case 9: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_time:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int64, ::google::protobuf::internal::WireFormatLite::TYPE_INT64>(
                 input, &time_)));
          set_has_time();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(82)) goto parse_compressionMode;
        break;
      }
      
      // required string compressionMode = 10;
      case 10: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_compressionMode:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_compressionmode()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8String(
            this->compressionmode().data(), this->compressionmode().length(),
            ::google::protobuf::internal::WireFormat::PARSE);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(90)) goto parse_compressionQuality;
        break;
      }
      
      // required string compressionQuality = 11;
      case 11: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_compressionQuality:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_compressionquality()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8String(
            this->compressionquality().data(), this->compressionquality().length(),
            ::google::protobuf::internal::WireFormat::PARSE);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(98)) goto parse_data;
        break;
      }
      
      // required bytes data = 12;
      case 12: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_data:
          DO_(::google::protobuf::internal::WireFormatLite::ReadBytes(
                input, this->mutable_data()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(106)) goto parse_metadata;
        break;
      }
      
      // optional string metadata = 13;
      case 13: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_metadata:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_metadata()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8String(
            this->metadata().data(), this->metadata().length(),
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

void RSBImage::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // required uint32 width = 1;
  if (has_width()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(1, this->width(), output);
  }
  
  // required uint32 height = 2;
  if (has_height()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(2, this->height(), output);
  }
  
  // required uint32 channels = 3;
  if (has_channels()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(3, this->channels(), output);
  }
  
  // required uint32 roix = 4;
  if (has_roix()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(4, this->roix(), output);
  }
  
  // required uint32 roiy = 5;
  if (has_roiy()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(5, this->roiy(), output);
  }
  
  // required uint32 roiw = 6;
  if (has_roiw()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(6, this->roiw(), output);
  }
  
  // required uint32 roih = 7;
  if (has_roih()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(7, this->roih(), output);
  }
  
  // required .icl.RSBImage.Format format = 8;
  if (has_format()) {
    ::google::protobuf::internal::WireFormatLite::WriteEnum(
      8, this->format(), output);
  }
  
  // required int64 time = 9;
  if (has_time()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt64(9, this->time(), output);
  }
  
  // required string compressionMode = 10;
  if (has_compressionmode()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->compressionmode().data(), this->compressionmode().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      10, this->compressionmode(), output);
  }
  
  // required string compressionQuality = 11;
  if (has_compressionquality()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->compressionquality().data(), this->compressionquality().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      11, this->compressionquality(), output);
  }
  
  // required bytes data = 12;
  if (has_data()) {
    ::google::protobuf::internal::WireFormatLite::WriteBytes(
      12, this->data(), output);
  }
  
  // optional string metadata = 13;
  if (has_metadata()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->metadata().data(), this->metadata().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      13, this->metadata(), output);
  }
  
  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* RSBImage::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // required uint32 width = 1;
  if (has_width()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(1, this->width(), target);
  }
  
  // required uint32 height = 2;
  if (has_height()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(2, this->height(), target);
  }
  
  // required uint32 channels = 3;
  if (has_channels()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(3, this->channels(), target);
  }
  
  // required uint32 roix = 4;
  if (has_roix()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(4, this->roix(), target);
  }
  
  // required uint32 roiy = 5;
  if (has_roiy()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(5, this->roiy(), target);
  }
  
  // required uint32 roiw = 6;
  if (has_roiw()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(6, this->roiw(), target);
  }
  
  // required uint32 roih = 7;
  if (has_roih()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(7, this->roih(), target);
  }
  
  // required .icl.RSBImage.Format format = 8;
  if (has_format()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteEnumToArray(
      8, this->format(), target);
  }
  
  // required int64 time = 9;
  if (has_time()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt64ToArray(9, this->time(), target);
  }
  
  // required string compressionMode = 10;
  if (has_compressionmode()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->compressionmode().data(), this->compressionmode().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        10, this->compressionmode(), target);
  }
  
  // required string compressionQuality = 11;
  if (has_compressionquality()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->compressionquality().data(), this->compressionquality().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        11, this->compressionquality(), target);
  }
  
  // required bytes data = 12;
  if (has_data()) {
    target =
      ::google::protobuf::internal::WireFormatLite::WriteBytesToArray(
        12, this->data(), target);
  }
  
  // optional string metadata = 13;
  if (has_metadata()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->metadata().data(), this->metadata().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        13, this->metadata(), target);
  }
  
  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int RSBImage::ByteSize() const {
  int total_size = 0;
  
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required uint32 width = 1;
    if (has_width()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->width());
    }
    
    // required uint32 height = 2;
    if (has_height()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->height());
    }
    
    // required uint32 channels = 3;
    if (has_channels()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->channels());
    }
    
    // required uint32 roix = 4;
    if (has_roix()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->roix());
    }
    
    // required uint32 roiy = 5;
    if (has_roiy()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->roiy());
    }
    
    // required uint32 roiw = 6;
    if (has_roiw()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->roiw());
    }
    
    // required uint32 roih = 7;
    if (has_roih()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->roih());
    }
    
    // required .icl.RSBImage.Format format = 8;
    if (has_format()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::EnumSize(this->format());
    }
    
  }
  if (_has_bits_[8 / 32] & (0xffu << (8 % 32))) {
    // required int64 time = 9;
    if (has_time()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int64Size(
          this->time());
    }
    
    // required string compressionMode = 10;
    if (has_compressionmode()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->compressionmode());
    }
    
    // required string compressionQuality = 11;
    if (has_compressionquality()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->compressionquality());
    }
    
    // required bytes data = 12;
    if (has_data()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::BytesSize(
          this->data());
    }
    
    // optional string metadata = 13;
    if (has_metadata()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->metadata());
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

void RSBImage::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const RSBImage* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const RSBImage*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void RSBImage::MergeFrom(const RSBImage& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_width()) {
      set_width(from.width());
    }
    if (from.has_height()) {
      set_height(from.height());
    }
    if (from.has_channels()) {
      set_channels(from.channels());
    }
    if (from.has_roix()) {
      set_roix(from.roix());
    }
    if (from.has_roiy()) {
      set_roiy(from.roiy());
    }
    if (from.has_roiw()) {
      set_roiw(from.roiw());
    }
    if (from.has_roih()) {
      set_roih(from.roih());
    }
    if (from.has_format()) {
      set_format(from.format());
    }
  }
  if (from._has_bits_[8 / 32] & (0xffu << (8 % 32))) {
    if (from.has_time()) {
      set_time(from.time());
    }
    if (from.has_compressionmode()) {
      set_compressionmode(from.compressionmode());
    }
    if (from.has_compressionquality()) {
      set_compressionquality(from.compressionquality());
    }
    if (from.has_data()) {
      set_data(from.data());
    }
    if (from.has_metadata()) {
      set_metadata(from.metadata());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void RSBImage::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void RSBImage::CopyFrom(const RSBImage& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool RSBImage::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000fff) != 0x00000fff) return false;
  
  return true;
}

void RSBImage::Swap(RSBImage* other) {
  if (other != this) {
    std::swap(width_, other->width_);
    std::swap(height_, other->height_);
    std::swap(channels_, other->channels_);
    std::swap(roix_, other->roix_);
    std::swap(roiy_, other->roiy_);
    std::swap(roiw_, other->roiw_);
    std::swap(roih_, other->roih_);
    std::swap(format_, other->format_);
    std::swap(time_, other->time_);
    std::swap(compressionmode_, other->compressionmode_);
    std::swap(compressionquality_, other->compressionquality_);
    std::swap(data_, other->data_);
    std::swap(metadata_, other->metadata_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata RSBImage::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = RSBImage_descriptor_;
  metadata.reflection = RSBImage_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace icl

// @@protoc_insertion_point(global_scope)