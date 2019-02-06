// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: keyValue.proto

#ifndef PROTOBUF_INCLUDED_keyValue_2eproto
#define PROTOBUF_INCLUDED_keyValue_2eproto

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3006001
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3006001 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/inlined_string_field.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#define PROTOBUF_INTERNAL_EXPORT_protobuf_keyValue_2eproto 

namespace protobuf_keyValue_2eproto {
// Internal implementation detail -- do not use these members.
struct TableStruct {
  static const ::google::protobuf::internal::ParseTableField entries[];
  static const ::google::protobuf::internal::AuxillaryParseTableField aux[];
  static const ::google::protobuf::internal::ParseTable schema[6];
  static const ::google::protobuf::internal::FieldMetadata field_metadata[];
  static const ::google::protobuf::internal::SerializationTable serialization_table[];
  static const ::google::protobuf::uint32 offsets[];
};
void AddDescriptors();
}  // namespace protobuf_keyValue_2eproto
namespace chirp {
class DeleteReply;
class DeleteReplyDefaultTypeInternal;
extern DeleteReplyDefaultTypeInternal _DeleteReply_default_instance_;
class DeleteRequest;
class DeleteRequestDefaultTypeInternal;
extern DeleteRequestDefaultTypeInternal _DeleteRequest_default_instance_;
class GetReply;
class GetReplyDefaultTypeInternal;
extern GetReplyDefaultTypeInternal _GetReply_default_instance_;
class GetRequest;
class GetRequestDefaultTypeInternal;
extern GetRequestDefaultTypeInternal _GetRequest_default_instance_;
class PutReply;
class PutReplyDefaultTypeInternal;
extern PutReplyDefaultTypeInternal _PutReply_default_instance_;
class PutRequest;
class PutRequestDefaultTypeInternal;
extern PutRequestDefaultTypeInternal _PutRequest_default_instance_;
}  // namespace chirp
namespace google {
namespace protobuf {
template<> ::chirp::DeleteReply* Arena::CreateMaybeMessage<::chirp::DeleteReply>(Arena*);
template<> ::chirp::DeleteRequest* Arena::CreateMaybeMessage<::chirp::DeleteRequest>(Arena*);
template<> ::chirp::GetReply* Arena::CreateMaybeMessage<::chirp::GetReply>(Arena*);
template<> ::chirp::GetRequest* Arena::CreateMaybeMessage<::chirp::GetRequest>(Arena*);
template<> ::chirp::PutReply* Arena::CreateMaybeMessage<::chirp::PutReply>(Arena*);
template<> ::chirp::PutRequest* Arena::CreateMaybeMessage<::chirp::PutRequest>(Arena*);
}  // namespace protobuf
}  // namespace google
namespace chirp {

// ===================================================================

class PutRequest : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:chirp.PutRequest) */ {
 public:
  PutRequest();
  virtual ~PutRequest();

  PutRequest(const PutRequest& from);

  inline PutRequest& operator=(const PutRequest& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  PutRequest(PutRequest&& from) noexcept
    : PutRequest() {
    *this = ::std::move(from);
  }

  inline PutRequest& operator=(PutRequest&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const PutRequest& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const PutRequest* internal_default_instance() {
    return reinterpret_cast<const PutRequest*>(
               &_PutRequest_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  void Swap(PutRequest* other);
  friend void swap(PutRequest& a, PutRequest& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline PutRequest* New() const final {
    return CreateMaybeMessage<PutRequest>(NULL);
  }

  PutRequest* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<PutRequest>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const PutRequest& from);
  void MergeFrom(const PutRequest& from);
  void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) final;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const final;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(PutRequest* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // bytes key = 1;
  void clear_key();
  static const int kKeyFieldNumber = 1;
  const ::std::string& key() const;
  void set_key(const ::std::string& value);
  #if LANG_CXX11
  void set_key(::std::string&& value);
  #endif
  void set_key(const char* value);
  void set_key(const void* value, size_t size);
  ::std::string* mutable_key();
  ::std::string* release_key();
  void set_allocated_key(::std::string* key);

  // bytes value = 2;
  void clear_value();
  static const int kValueFieldNumber = 2;
  const ::std::string& value() const;
  void set_value(const ::std::string& value);
  #if LANG_CXX11
  void set_value(::std::string&& value);
  #endif
  void set_value(const char* value);
  void set_value(const void* value, size_t size);
  ::std::string* mutable_value();
  ::std::string* release_value();
  void set_allocated_value(::std::string* value);

  // @@protoc_insertion_point(class_scope:chirp.PutRequest)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::ArenaStringPtr key_;
  ::google::protobuf::internal::ArenaStringPtr value_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  friend struct ::protobuf_keyValue_2eproto::TableStruct;
};
// -------------------------------------------------------------------

class PutReply : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:chirp.PutReply) */ {
 public:
  PutReply();
  virtual ~PutReply();

  PutReply(const PutReply& from);

  inline PutReply& operator=(const PutReply& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  PutReply(PutReply&& from) noexcept
    : PutReply() {
    *this = ::std::move(from);
  }

  inline PutReply& operator=(PutReply&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const PutReply& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const PutReply* internal_default_instance() {
    return reinterpret_cast<const PutReply*>(
               &_PutReply_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    1;

  void Swap(PutReply* other);
  friend void swap(PutReply& a, PutReply& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline PutReply* New() const final {
    return CreateMaybeMessage<PutReply>(NULL);
  }

  PutReply* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<PutReply>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const PutReply& from);
  void MergeFrom(const PutReply& from);
  void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) final;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const final;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(PutReply* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // @@protoc_insertion_point(class_scope:chirp.PutReply)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  friend struct ::protobuf_keyValue_2eproto::TableStruct;
};
// -------------------------------------------------------------------

class GetRequest : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:chirp.GetRequest) */ {
 public:
  GetRequest();
  virtual ~GetRequest();

  GetRequest(const GetRequest& from);

  inline GetRequest& operator=(const GetRequest& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  GetRequest(GetRequest&& from) noexcept
    : GetRequest() {
    *this = ::std::move(from);
  }

  inline GetRequest& operator=(GetRequest&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const GetRequest& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const GetRequest* internal_default_instance() {
    return reinterpret_cast<const GetRequest*>(
               &_GetRequest_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    2;

  void Swap(GetRequest* other);
  friend void swap(GetRequest& a, GetRequest& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline GetRequest* New() const final {
    return CreateMaybeMessage<GetRequest>(NULL);
  }

  GetRequest* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<GetRequest>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const GetRequest& from);
  void MergeFrom(const GetRequest& from);
  void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) final;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const final;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(GetRequest* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // bytes key = 1;
  void clear_key();
  static const int kKeyFieldNumber = 1;
  const ::std::string& key() const;
  void set_key(const ::std::string& value);
  #if LANG_CXX11
  void set_key(::std::string&& value);
  #endif
  void set_key(const char* value);
  void set_key(const void* value, size_t size);
  ::std::string* mutable_key();
  ::std::string* release_key();
  void set_allocated_key(::std::string* key);

  // @@protoc_insertion_point(class_scope:chirp.GetRequest)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::ArenaStringPtr key_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  friend struct ::protobuf_keyValue_2eproto::TableStruct;
};
// -------------------------------------------------------------------

class GetReply : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:chirp.GetReply) */ {
 public:
  GetReply();
  virtual ~GetReply();

  GetReply(const GetReply& from);

  inline GetReply& operator=(const GetReply& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  GetReply(GetReply&& from) noexcept
    : GetReply() {
    *this = ::std::move(from);
  }

  inline GetReply& operator=(GetReply&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const GetReply& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const GetReply* internal_default_instance() {
    return reinterpret_cast<const GetReply*>(
               &_GetReply_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    3;

  void Swap(GetReply* other);
  friend void swap(GetReply& a, GetReply& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline GetReply* New() const final {
    return CreateMaybeMessage<GetReply>(NULL);
  }

  GetReply* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<GetReply>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const GetReply& from);
  void MergeFrom(const GetReply& from);
  void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) final;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const final;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(GetReply* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // bytes value = 1;
  void clear_value();
  static const int kValueFieldNumber = 1;
  const ::std::string& value() const;
  void set_value(const ::std::string& value);
  #if LANG_CXX11
  void set_value(::std::string&& value);
  #endif
  void set_value(const char* value);
  void set_value(const void* value, size_t size);
  ::std::string* mutable_value();
  ::std::string* release_value();
  void set_allocated_value(::std::string* value);

  // @@protoc_insertion_point(class_scope:chirp.GetReply)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::ArenaStringPtr value_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  friend struct ::protobuf_keyValue_2eproto::TableStruct;
};
// -------------------------------------------------------------------

class DeleteRequest : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:chirp.DeleteRequest) */ {
 public:
  DeleteRequest();
  virtual ~DeleteRequest();

  DeleteRequest(const DeleteRequest& from);

  inline DeleteRequest& operator=(const DeleteRequest& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  DeleteRequest(DeleteRequest&& from) noexcept
    : DeleteRequest() {
    *this = ::std::move(from);
  }

  inline DeleteRequest& operator=(DeleteRequest&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const DeleteRequest& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const DeleteRequest* internal_default_instance() {
    return reinterpret_cast<const DeleteRequest*>(
               &_DeleteRequest_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    4;

  void Swap(DeleteRequest* other);
  friend void swap(DeleteRequest& a, DeleteRequest& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline DeleteRequest* New() const final {
    return CreateMaybeMessage<DeleteRequest>(NULL);
  }

  DeleteRequest* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<DeleteRequest>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const DeleteRequest& from);
  void MergeFrom(const DeleteRequest& from);
  void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) final;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const final;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(DeleteRequest* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // bytes key = 1;
  void clear_key();
  static const int kKeyFieldNumber = 1;
  const ::std::string& key() const;
  void set_key(const ::std::string& value);
  #if LANG_CXX11
  void set_key(::std::string&& value);
  #endif
  void set_key(const char* value);
  void set_key(const void* value, size_t size);
  ::std::string* mutable_key();
  ::std::string* release_key();
  void set_allocated_key(::std::string* key);

  // @@protoc_insertion_point(class_scope:chirp.DeleteRequest)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::ArenaStringPtr key_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  friend struct ::protobuf_keyValue_2eproto::TableStruct;
};
// -------------------------------------------------------------------

class DeleteReply : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:chirp.DeleteReply) */ {
 public:
  DeleteReply();
  virtual ~DeleteReply();

  DeleteReply(const DeleteReply& from);

  inline DeleteReply& operator=(const DeleteReply& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  DeleteReply(DeleteReply&& from) noexcept
    : DeleteReply() {
    *this = ::std::move(from);
  }

  inline DeleteReply& operator=(DeleteReply&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const DeleteReply& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const DeleteReply* internal_default_instance() {
    return reinterpret_cast<const DeleteReply*>(
               &_DeleteReply_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    5;

  void Swap(DeleteReply* other);
  friend void swap(DeleteReply& a, DeleteReply& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline DeleteReply* New() const final {
    return CreateMaybeMessage<DeleteReply>(NULL);
  }

  DeleteReply* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<DeleteReply>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const DeleteReply& from);
  void MergeFrom(const DeleteReply& from);
  void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) final;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const final;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(DeleteReply* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // @@protoc_insertion_point(class_scope:chirp.DeleteReply)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  friend struct ::protobuf_keyValue_2eproto::TableStruct;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// PutRequest

// bytes key = 1;
inline void PutRequest::clear_key() {
  key_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& PutRequest::key() const {
  // @@protoc_insertion_point(field_get:chirp.PutRequest.key)
  return key_.GetNoArena();
}
inline void PutRequest::set_key(const ::std::string& value) {
  
  key_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:chirp.PutRequest.key)
}
#if LANG_CXX11
inline void PutRequest::set_key(::std::string&& value) {
  
  key_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:chirp.PutRequest.key)
}
#endif
inline void PutRequest::set_key(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  
  key_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:chirp.PutRequest.key)
}
inline void PutRequest::set_key(const void* value, size_t size) {
  
  key_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:chirp.PutRequest.key)
}
inline ::std::string* PutRequest::mutable_key() {
  
  // @@protoc_insertion_point(field_mutable:chirp.PutRequest.key)
  return key_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* PutRequest::release_key() {
  // @@protoc_insertion_point(field_release:chirp.PutRequest.key)
  
  return key_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void PutRequest::set_allocated_key(::std::string* key) {
  if (key != NULL) {
    
  } else {
    
  }
  key_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), key);
  // @@protoc_insertion_point(field_set_allocated:chirp.PutRequest.key)
}

// bytes value = 2;
inline void PutRequest::clear_value() {
  value_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& PutRequest::value() const {
  // @@protoc_insertion_point(field_get:chirp.PutRequest.value)
  return value_.GetNoArena();
}
inline void PutRequest::set_value(const ::std::string& value) {
  
  value_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:chirp.PutRequest.value)
}
#if LANG_CXX11
inline void PutRequest::set_value(::std::string&& value) {
  
  value_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:chirp.PutRequest.value)
}
#endif
inline void PutRequest::set_value(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  
  value_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:chirp.PutRequest.value)
}
inline void PutRequest::set_value(const void* value, size_t size) {
  
  value_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:chirp.PutRequest.value)
}
inline ::std::string* PutRequest::mutable_value() {
  
  // @@protoc_insertion_point(field_mutable:chirp.PutRequest.value)
  return value_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* PutRequest::release_value() {
  // @@protoc_insertion_point(field_release:chirp.PutRequest.value)
  
  return value_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void PutRequest::set_allocated_value(::std::string* value) {
  if (value != NULL) {
    
  } else {
    
  }
  value_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set_allocated:chirp.PutRequest.value)
}

// -------------------------------------------------------------------

// PutReply

// -------------------------------------------------------------------

// GetRequest

// bytes key = 1;
inline void GetRequest::clear_key() {
  key_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& GetRequest::key() const {
  // @@protoc_insertion_point(field_get:chirp.GetRequest.key)
  return key_.GetNoArena();
}
inline void GetRequest::set_key(const ::std::string& value) {
  
  key_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:chirp.GetRequest.key)
}
#if LANG_CXX11
inline void GetRequest::set_key(::std::string&& value) {
  
  key_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:chirp.GetRequest.key)
}
#endif
inline void GetRequest::set_key(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  
  key_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:chirp.GetRequest.key)
}
inline void GetRequest::set_key(const void* value, size_t size) {
  
  key_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:chirp.GetRequest.key)
}
inline ::std::string* GetRequest::mutable_key() {
  
  // @@protoc_insertion_point(field_mutable:chirp.GetRequest.key)
  return key_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* GetRequest::release_key() {
  // @@protoc_insertion_point(field_release:chirp.GetRequest.key)
  
  return key_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void GetRequest::set_allocated_key(::std::string* key) {
  if (key != NULL) {
    
  } else {
    
  }
  key_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), key);
  // @@protoc_insertion_point(field_set_allocated:chirp.GetRequest.key)
}

// -------------------------------------------------------------------

// GetReply

// bytes value = 1;
inline void GetReply::clear_value() {
  value_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& GetReply::value() const {
  // @@protoc_insertion_point(field_get:chirp.GetReply.value)
  return value_.GetNoArena();
}
inline void GetReply::set_value(const ::std::string& value) {
  
  value_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:chirp.GetReply.value)
}
#if LANG_CXX11
inline void GetReply::set_value(::std::string&& value) {
  
  value_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:chirp.GetReply.value)
}
#endif
inline void GetReply::set_value(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  
  value_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:chirp.GetReply.value)
}
inline void GetReply::set_value(const void* value, size_t size) {
  
  value_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:chirp.GetReply.value)
}
inline ::std::string* GetReply::mutable_value() {
  
  // @@protoc_insertion_point(field_mutable:chirp.GetReply.value)
  return value_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* GetReply::release_value() {
  // @@protoc_insertion_point(field_release:chirp.GetReply.value)
  
  return value_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void GetReply::set_allocated_value(::std::string* value) {
  if (value != NULL) {
    
  } else {
    
  }
  value_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set_allocated:chirp.GetReply.value)
}

// -------------------------------------------------------------------

// DeleteRequest

// bytes key = 1;
inline void DeleteRequest::clear_key() {
  key_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& DeleteRequest::key() const {
  // @@protoc_insertion_point(field_get:chirp.DeleteRequest.key)
  return key_.GetNoArena();
}
inline void DeleteRequest::set_key(const ::std::string& value) {
  
  key_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:chirp.DeleteRequest.key)
}
#if LANG_CXX11
inline void DeleteRequest::set_key(::std::string&& value) {
  
  key_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:chirp.DeleteRequest.key)
}
#endif
inline void DeleteRequest::set_key(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  
  key_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:chirp.DeleteRequest.key)
}
inline void DeleteRequest::set_key(const void* value, size_t size) {
  
  key_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:chirp.DeleteRequest.key)
}
inline ::std::string* DeleteRequest::mutable_key() {
  
  // @@protoc_insertion_point(field_mutable:chirp.DeleteRequest.key)
  return key_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* DeleteRequest::release_key() {
  // @@protoc_insertion_point(field_release:chirp.DeleteRequest.key)
  
  return key_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void DeleteRequest::set_allocated_key(::std::string* key) {
  if (key != NULL) {
    
  } else {
    
  }
  key_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), key);
  // @@protoc_insertion_point(field_set_allocated:chirp.DeleteRequest.key)
}

// -------------------------------------------------------------------

// DeleteReply

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------

// -------------------------------------------------------------------

// -------------------------------------------------------------------

// -------------------------------------------------------------------

// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace chirp

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_INCLUDED_keyValue_2eproto
