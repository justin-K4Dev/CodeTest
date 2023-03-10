// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: protocol.Packet.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_protocol_2ePacket_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_protocol_2ePacket_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3019000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3019006 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata_lite.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
#include <google/protobuf/timestamp.pb.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_protocol_2ePacket_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_protocol_2ePacket_2eproto {
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTableField entries[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::AuxiliaryParseTableField aux[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTable schema[3]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::FieldMetadata field_metadata[];
  static const ::PROTOBUF_NAMESPACE_ID::internal::SerializationTable serialization_table[];
  static const uint32_t offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_protocol_2ePacket_2eproto;
namespace Protocol {
class Character;
struct CharacterDefaultTypeInternal;
extern CharacterDefaultTypeInternal _Character_default_instance_;
class Item;
struct ItemDefaultTypeInternal;
extern ItemDefaultTypeInternal _Item_default_instance_;
class Player;
struct PlayerDefaultTypeInternal;
extern PlayerDefaultTypeInternal _Player_default_instance_;
}  // namespace Protocol
PROTOBUF_NAMESPACE_OPEN
template<> ::Protocol::Character* Arena::CreateMaybeMessage<::Protocol::Character>(Arena*);
template<> ::Protocol::Item* Arena::CreateMaybeMessage<::Protocol::Item>(Arena*);
template<> ::Protocol::Player* Arena::CreateMaybeMessage<::Protocol::Player>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace Protocol {

// ===================================================================

class Item final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:Protocol.Item) */ {
 public:
  inline Item() : Item(nullptr) {}
  ~Item() override;
  explicit constexpr Item(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  Item(const Item& from);
  Item(Item&& from) noexcept
    : Item() {
    *this = ::std::move(from);
  }

  inline Item& operator=(const Item& from) {
    CopyFrom(from);
    return *this;
  }
  inline Item& operator=(Item&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()
  #ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetOwningArena() != nullptr
  #endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const Item& default_instance() {
    return *internal_default_instance();
  }
  static inline const Item* internal_default_instance() {
    return reinterpret_cast<const Item*>(
               &_Item_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(Item& a, Item& b) {
    a.Swap(&b);
  }
  inline void Swap(Item* other) {
    if (other == this) return;
  #ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() != nullptr &&
        GetOwningArena() == other->GetOwningArena()) {
   #else  // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() == other->GetOwningArena()) {
  #endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(Item* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  Item* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<Item>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const Item& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom(const Item& from);
  private:
  static void MergeImpl(::PROTOBUF_NAMESPACE_ID::Message* to, const ::PROTOBUF_NAMESPACE_ID::Message& from);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  uint8_t* _InternalSerialize(
      uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(Item* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "Protocol.Item";
  }
  protected:
  explicit Item(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kUUIDFieldNumber = 1,
    kTIDFieldNumber = 2,
  };
  // uint64 UUID = 1;
  void clear_uuid();
  uint64_t uuid() const;
  void set_uuid(uint64_t value);
  private:
  uint64_t _internal_uuid() const;
  void _internal_set_uuid(uint64_t value);
  public:

  // uint32 TID = 2;
  void clear_tid();
  uint32_t tid() const;
  void set_tid(uint32_t value);
  private:
  uint32_t _internal_tid() const;
  void _internal_set_tid(uint32_t value);
  public:

  // @@protoc_insertion_point(class_scope:Protocol.Item)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  uint64_t uuid_;
  uint32_t tid_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_protocol_2ePacket_2eproto;
};
// -------------------------------------------------------------------

class Character final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:Protocol.Character) */ {
 public:
  inline Character() : Character(nullptr) {}
  ~Character() override;
  explicit constexpr Character(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  Character(const Character& from);
  Character(Character&& from) noexcept
    : Character() {
    *this = ::std::move(from);
  }

  inline Character& operator=(const Character& from) {
    CopyFrom(from);
    return *this;
  }
  inline Character& operator=(Character&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()
  #ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetOwningArena() != nullptr
  #endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const Character& default_instance() {
    return *internal_default_instance();
  }
  static inline const Character* internal_default_instance() {
    return reinterpret_cast<const Character*>(
               &_Character_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    1;

  friend void swap(Character& a, Character& b) {
    a.Swap(&b);
  }
  inline void Swap(Character* other) {
    if (other == this) return;
  #ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() != nullptr &&
        GetOwningArena() == other->GetOwningArena()) {
   #else  // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() == other->GetOwningArena()) {
  #endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(Character* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  Character* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<Character>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const Character& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom(const Character& from);
  private:
  static void MergeImpl(::PROTOBUF_NAMESPACE_ID::Message* to, const ::PROTOBUF_NAMESPACE_ID::Message& from);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  uint8_t* _InternalSerialize(
      uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(Character* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "Protocol.Character";
  }
  protected:
  explicit Character(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kItemFieldNumber = 3,
    kUUIDFieldNumber = 1,
    kTIDFieldNumber = 2,
  };
  // repeated .Protocol.Item item = 3;
  int item_size() const;
  private:
  int _internal_item_size() const;
  public:
  void clear_item();
  ::Protocol::Item* mutable_item(int index);
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::Protocol::Item >*
      mutable_item();
  private:
  const ::Protocol::Item& _internal_item(int index) const;
  ::Protocol::Item* _internal_add_item();
  public:
  const ::Protocol::Item& item(int index) const;
  ::Protocol::Item* add_item();
  const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::Protocol::Item >&
      item() const;

  // uint64 UUID = 1;
  void clear_uuid();
  uint64_t uuid() const;
  void set_uuid(uint64_t value);
  private:
  uint64_t _internal_uuid() const;
  void _internal_set_uuid(uint64_t value);
  public:

  // uint32 TID = 2;
  void clear_tid();
  uint32_t tid() const;
  void set_tid(uint32_t value);
  private:
  uint32_t _internal_tid() const;
  void _internal_set_tid(uint32_t value);
  public:

  // @@protoc_insertion_point(class_scope:Protocol.Character)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::Protocol::Item > item_;
  uint64_t uuid_;
  uint32_t tid_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_protocol_2ePacket_2eproto;
};
// -------------------------------------------------------------------

class Player final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:Protocol.Player) */ {
 public:
  inline Player() : Player(nullptr) {}
  ~Player() override;
  explicit constexpr Player(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  Player(const Player& from);
  Player(Player&& from) noexcept
    : Player() {
    *this = ::std::move(from);
  }

  inline Player& operator=(const Player& from) {
    CopyFrom(from);
    return *this;
  }
  inline Player& operator=(Player&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()
  #ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetOwningArena() != nullptr
  #endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const Player& default_instance() {
    return *internal_default_instance();
  }
  static inline const Player* internal_default_instance() {
    return reinterpret_cast<const Player*>(
               &_Player_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    2;

  friend void swap(Player& a, Player& b) {
    a.Swap(&b);
  }
  inline void Swap(Player* other) {
    if (other == this) return;
  #ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() != nullptr &&
        GetOwningArena() == other->GetOwningArena()) {
   #else  // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() == other->GetOwningArena()) {
  #endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(Player* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  Player* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<Player>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const Player& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom(const Player& from);
  private:
  static void MergeImpl(::PROTOBUF_NAMESPACE_ID::Message* to, const ::PROTOBUF_NAMESPACE_ID::Message& from);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  uint8_t* _InternalSerialize(
      uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(Player* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "Protocol.Player";
  }
  protected:
  explicit Player(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kCharacterFieldNumber = 3,
    kNicknameFieldNumber = 2,
    kUUIDFieldNumber = 1,
  };
  // repeated .Protocol.Character character = 3;
  int character_size() const;
  private:
  int _internal_character_size() const;
  public:
  void clear_character();
  ::Protocol::Character* mutable_character(int index);
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::Protocol::Character >*
      mutable_character();
  private:
  const ::Protocol::Character& _internal_character(int index) const;
  ::Protocol::Character* _internal_add_character();
  public:
  const ::Protocol::Character& character(int index) const;
  ::Protocol::Character* add_character();
  const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::Protocol::Character >&
      character() const;

  // bytes nickname = 2;
  void clear_nickname();
  const std::string& nickname() const;
  template <typename ArgT0 = const std::string&, typename... ArgT>
  void set_nickname(ArgT0&& arg0, ArgT... args);
  std::string* mutable_nickname();
  PROTOBUF_NODISCARD std::string* release_nickname();
  void set_allocated_nickname(std::string* nickname);
  private:
  const std::string& _internal_nickname() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_nickname(const std::string& value);
  std::string* _internal_mutable_nickname();
  public:

  // uint64 UUID = 1;
  void clear_uuid();
  uint64_t uuid() const;
  void set_uuid(uint64_t value);
  private:
  uint64_t _internal_uuid() const;
  void _internal_set_uuid(uint64_t value);
  public:

  // @@protoc_insertion_point(class_scope:Protocol.Player)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::Protocol::Character > character_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr nickname_;
  uint64_t uuid_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_protocol_2ePacket_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// Item

// uint64 UUID = 1;
inline void Item::clear_uuid() {
  uuid_ = uint64_t{0u};
}
inline uint64_t Item::_internal_uuid() const {
  return uuid_;
}
inline uint64_t Item::uuid() const {
  // @@protoc_insertion_point(field_get:Protocol.Item.UUID)
  return _internal_uuid();
}
inline void Item::_internal_set_uuid(uint64_t value) {
  
  uuid_ = value;
}
inline void Item::set_uuid(uint64_t value) {
  _internal_set_uuid(value);
  // @@protoc_insertion_point(field_set:Protocol.Item.UUID)
}

// uint32 TID = 2;
inline void Item::clear_tid() {
  tid_ = 0u;
}
inline uint32_t Item::_internal_tid() const {
  return tid_;
}
inline uint32_t Item::tid() const {
  // @@protoc_insertion_point(field_get:Protocol.Item.TID)
  return _internal_tid();
}
inline void Item::_internal_set_tid(uint32_t value) {
  
  tid_ = value;
}
inline void Item::set_tid(uint32_t value) {
  _internal_set_tid(value);
  // @@protoc_insertion_point(field_set:Protocol.Item.TID)
}

// -------------------------------------------------------------------

// Character

// uint64 UUID = 1;
inline void Character::clear_uuid() {
  uuid_ = uint64_t{0u};
}
inline uint64_t Character::_internal_uuid() const {
  return uuid_;
}
inline uint64_t Character::uuid() const {
  // @@protoc_insertion_point(field_get:Protocol.Character.UUID)
  return _internal_uuid();
}
inline void Character::_internal_set_uuid(uint64_t value) {
  
  uuid_ = value;
}
inline void Character::set_uuid(uint64_t value) {
  _internal_set_uuid(value);
  // @@protoc_insertion_point(field_set:Protocol.Character.UUID)
}

// uint32 TID = 2;
inline void Character::clear_tid() {
  tid_ = 0u;
}
inline uint32_t Character::_internal_tid() const {
  return tid_;
}
inline uint32_t Character::tid() const {
  // @@protoc_insertion_point(field_get:Protocol.Character.TID)
  return _internal_tid();
}
inline void Character::_internal_set_tid(uint32_t value) {
  
  tid_ = value;
}
inline void Character::set_tid(uint32_t value) {
  _internal_set_tid(value);
  // @@protoc_insertion_point(field_set:Protocol.Character.TID)
}

// repeated .Protocol.Item item = 3;
inline int Character::_internal_item_size() const {
  return item_.size();
}
inline int Character::item_size() const {
  return _internal_item_size();
}
inline void Character::clear_item() {
  item_.Clear();
}
inline ::Protocol::Item* Character::mutable_item(int index) {
  // @@protoc_insertion_point(field_mutable:Protocol.Character.item)
  return item_.Mutable(index);
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::Protocol::Item >*
Character::mutable_item() {
  // @@protoc_insertion_point(field_mutable_list:Protocol.Character.item)
  return &item_;
}
inline const ::Protocol::Item& Character::_internal_item(int index) const {
  return item_.Get(index);
}
inline const ::Protocol::Item& Character::item(int index) const {
  // @@protoc_insertion_point(field_get:Protocol.Character.item)
  return _internal_item(index);
}
inline ::Protocol::Item* Character::_internal_add_item() {
  return item_.Add();
}
inline ::Protocol::Item* Character::add_item() {
  ::Protocol::Item* _add = _internal_add_item();
  // @@protoc_insertion_point(field_add:Protocol.Character.item)
  return _add;
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::Protocol::Item >&
Character::item() const {
  // @@protoc_insertion_point(field_list:Protocol.Character.item)
  return item_;
}

// -------------------------------------------------------------------

// Player

// uint64 UUID = 1;
inline void Player::clear_uuid() {
  uuid_ = uint64_t{0u};
}
inline uint64_t Player::_internal_uuid() const {
  return uuid_;
}
inline uint64_t Player::uuid() const {
  // @@protoc_insertion_point(field_get:Protocol.Player.UUID)
  return _internal_uuid();
}
inline void Player::_internal_set_uuid(uint64_t value) {
  
  uuid_ = value;
}
inline void Player::set_uuid(uint64_t value) {
  _internal_set_uuid(value);
  // @@protoc_insertion_point(field_set:Protocol.Player.UUID)
}

// bytes nickname = 2;
inline void Player::clear_nickname() {
  nickname_.ClearToEmpty();
}
inline const std::string& Player::nickname() const {
  // @@protoc_insertion_point(field_get:Protocol.Player.nickname)
  return _internal_nickname();
}
template <typename ArgT0, typename... ArgT>
inline PROTOBUF_ALWAYS_INLINE
void Player::set_nickname(ArgT0&& arg0, ArgT... args) {
 
 nickname_.SetBytes(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, static_cast<ArgT0 &&>(arg0), args..., GetArenaForAllocation());
  // @@protoc_insertion_point(field_set:Protocol.Player.nickname)
}
inline std::string* Player::mutable_nickname() {
  std::string* _s = _internal_mutable_nickname();
  // @@protoc_insertion_point(field_mutable:Protocol.Player.nickname)
  return _s;
}
inline const std::string& Player::_internal_nickname() const {
  return nickname_.Get();
}
inline void Player::_internal_set_nickname(const std::string& value) {
  
  nickname_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, value, GetArenaForAllocation());
}
inline std::string* Player::_internal_mutable_nickname() {
  
  return nickname_.Mutable(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, GetArenaForAllocation());
}
inline std::string* Player::release_nickname() {
  // @@protoc_insertion_point(field_release:Protocol.Player.nickname)
  return nickname_.Release(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArenaForAllocation());
}
inline void Player::set_allocated_nickname(std::string* nickname) {
  if (nickname != nullptr) {
    
  } else {
    
  }
  nickname_.SetAllocated(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), nickname,
      GetArenaForAllocation());
#ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (nickname_.IsDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited())) {
    nickname_.Set(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), "", GetArenaForAllocation());
  }
#endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:Protocol.Player.nickname)
}

// repeated .Protocol.Character character = 3;
inline int Player::_internal_character_size() const {
  return character_.size();
}
inline int Player::character_size() const {
  return _internal_character_size();
}
inline void Player::clear_character() {
  character_.Clear();
}
inline ::Protocol::Character* Player::mutable_character(int index) {
  // @@protoc_insertion_point(field_mutable:Protocol.Player.character)
  return character_.Mutable(index);
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::Protocol::Character >*
Player::mutable_character() {
  // @@protoc_insertion_point(field_mutable_list:Protocol.Player.character)
  return &character_;
}
inline const ::Protocol::Character& Player::_internal_character(int index) const {
  return character_.Get(index);
}
inline const ::Protocol::Character& Player::character(int index) const {
  // @@protoc_insertion_point(field_get:Protocol.Player.character)
  return _internal_character(index);
}
inline ::Protocol::Character* Player::_internal_add_character() {
  return character_.Add();
}
inline ::Protocol::Character* Player::add_character() {
  ::Protocol::Character* _add = _internal_add_character();
  // @@protoc_insertion_point(field_add:Protocol.Player.character)
  return _add;
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::Protocol::Character >&
Player::character() const {
  // @@protoc_insertion_point(field_list:Protocol.Player.character)
  return character_;
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------

// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace Protocol

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_protocol_2ePacket_2eproto
