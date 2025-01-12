/*
 * @
 * ������COM�I�u�W�F�N�g�𗘗p���邽�߁ALoadTexture�֐������InitSound�֐��Ăяo����
 * �G���[�ɂȂ�
 */
#ifndef __SOUND_H__
#define __SOUND_H__

#include <xaudio2.h>
#pragma comment(lib, "xaudio2.lib")

//----------
// �v���g�^�C�v�錾
//----------
HRESULT InitSound(void);
void UninitSound(void);

// �T�E���h�t�@�C���̓ǂݍ���
XAUDIO2_BUFFER* LoadSound(const char *file, bool loop = false);

// �T�E���h�̍Đ�
#undef PlaySound // winapi��PlaySound�𖳌��ɂ���
IXAudio2SourceVoice* PlaySound(XAUDIO2_BUFFER* pSound);

#endif // __SOUND_H__