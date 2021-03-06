// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_MESSAGE_MESSAGE_H_
#define FLATBUFFERS_GENERATED_MESSAGE_MESSAGE_H_

#include "flatbuffers.h"

namespace Message {

struct Msg;

struct Msg FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum {
    VT_OBJET = 4,
    VT_MESSAGE = 6,
    VT_X = 8
  };
  const flatbuffers::String *objet() const {
    return GetPointer<const flatbuffers::String *>(VT_OBJET);
  }
  const flatbuffers::String *message() const {
    return GetPointer<const flatbuffers::String *>(VT_MESSAGE);
  }
  float x() const {
    return GetField<float>(VT_X, 0.0f);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<flatbuffers::uoffset_t>(verifier, VT_OBJET) &&
           verifier.Verify(objet()) &&
           VerifyField<flatbuffers::uoffset_t>(verifier, VT_MESSAGE) &&
           verifier.Verify(message()) &&
           VerifyField<float>(verifier, VT_X) &&
           verifier.EndTable();
  }
};

struct MsgBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_objet(flatbuffers::Offset<flatbuffers::String> objet) {
    fbb_.AddOffset(Msg::VT_OBJET, objet);
  }
  void add_message(flatbuffers::Offset<flatbuffers::String> message) {
    fbb_.AddOffset(Msg::VT_MESSAGE, message);
  }
  void add_x(float x) {
    fbb_.AddElement<float>(Msg::VT_X, x, 0.0f);
  }
  MsgBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  MsgBuilder &operator=(const MsgBuilder &);
  flatbuffers::Offset<Msg> Finish() {
    const auto end = fbb_.EndTable(start_, 3);
    auto o = flatbuffers::Offset<Msg>(end);
    return o;
  }
};

inline flatbuffers::Offset<Msg> CreateMsg(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<flatbuffers::String> objet = 0,
    flatbuffers::Offset<flatbuffers::String> message = 0,
    float x = 0.0f) {
  MsgBuilder builder_(_fbb);
  builder_.add_x(x);
  builder_.add_message(message);
  builder_.add_objet(objet);
  return builder_.Finish();
}

inline flatbuffers::Offset<Msg> CreateMsgDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    const char *objet = nullptr,
    const char *message = nullptr,
    float x = 0.0f) {
  return Message::CreateMsg(
      _fbb,
      objet ? _fbb.CreateString(objet) : 0,
      message ? _fbb.CreateString(message) : 0,
      x);
}

inline const Message::Msg *GetMsg(const void *buf) {
  return flatbuffers::GetRoot<Message::Msg>(buf);
}

inline bool VerifyMsgBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifyBuffer<Message::Msg>(nullptr);
}

inline void FinishMsgBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<Message::Msg> root) {
  fbb.Finish(root);
}

}  // namespace Message

#endif  // FLATBUFFERS_GENERATED_MESSAGE_MESSAGE_H_
