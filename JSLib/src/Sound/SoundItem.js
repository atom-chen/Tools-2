using UnityEngine;

namespace SDK.Lib
{
    public enum SoundPlayState
    {
        eSS_None,           // Ĭ��״̬
        eSS_Play,           // ����״̬
        eSS_Stop,           // ��ͣ״̬
        eSS_Pause,           // ֹͣ״̬
    }

    public enum SoundResType
    {
        eSRT_Prefab,
        eSRT_Clip,
    }

    /**
     * @brief ���ֺ���Ч���������
     */
    public class SoundItem
    {
        public string m_path;           // ��ԴĿ¼
        public SoundResType m_soundResType = SoundResType.eSRT_Prefab;
        protected SoundPlayState m_playState = SoundPlayState.eSS_None;      // ������Ч����״̬
        public Transform m_trans;       // λ����Ϣ
        public GameObject m_go;         // audio ��� GameObject ����
        public AudioSource m_audio;             // ��Դ
        public bool m_playOnStart = true;

        public ulong m_delay = 0;
        public bool m_bypassEffects = false;        // �Ƿ�����Ƶ��Ч
        public bool m_mute = false;         // �Ƿ���
        public bool m_bLoop = false;        // �Ƿ�ѭ������
        public float m_volume = 1.0f;
        public float m_pitch = 1.0f;
        public bool m_ScaleOutputVolume = true;

        public SoundItem()
        {

        }

        public bool bInCurState(SoundPlayState state)
        {
            return m_playState == state;
        }

        public virtual void setResObj(UnityEngine.Object go_)
        {

        }

        public void initParam(SoundParam soundParam)
        {
            m_trans = soundParam.m_trans;
            m_bLoop = soundParam.m_bLoop;
            m_path = soundParam.m_path;
        }

        protected void updateParam()
        {
            if (m_trans != null)
            {
                m_go.transform.position = m_trans.position;
            }
            m_audio = m_go.GetComponent<AudioSource>();
            //m_audio.rolloffMode = AudioRolloffMode.Logarithmic;
            m_audio.loop = m_bLoop;
            //m_audio.dopplerLevel = 0f;
            //m_audio.spatialBlend = 0f;
            volume = m_volume;

            //m_audio.minDistance = 1.0f;
            //m_audio.maxDistance = 50;
        }

        public float volume
        {
            get 
            { 
                return m_volume; 
            }
            set
            {
                if (m_ScaleOutputVolume)
                {
                    m_audio.volume = ScaleVolume(value);
                }
                else
                {
                    m_audio.volume = value;
                }
                m_volume = value;
            }
        }

        public float pitch
        {
            get 
            {
                return m_pitch; 
            }
            set
            {
                m_audio.pitch = value;
                m_pitch = value;
            }
        }

        void Start()
        {
            if (m_playOnStart)
            {
                Play();
            }
        }

        public void Pause()
        {
            m_playState = SoundPlayState.eSS_Pause;
            m_audio.Pause();
        }

        public void Play()
        {
            if (SoundPlayState.eSS_Pause == m_playState)
            {
                m_audio.UnPause();
            }
            else
            {
                m_audio.Play(m_delay);
            }

            m_playState = SoundPlayState.eSS_Play;
        }

        public void Stop()
        {
            m_playState = SoundPlayState.eSS_Stop;
            m_audio.Stop();
        }

        public void SetPitch(float p)
        {
            pitch = p;
        }

        // TODO: we should consider using this dB scale as an option when porting these changes
        // over to unity-bowerbird: http://wiki.unity3d.com/index.php?title=Loudness
        /*
        * Quadratic scaling of actual volume used by AudioSource. Approximates the proper exponential.
        */
        public float ScaleVolume(float v)
        {
            v = Mathf.Pow(v, 4);
            return Mathf.Clamp(v, 0f, 1f);
        }

        // ж��
        public virtual void unload()
        {
            
        }

        public bool isEnd()
        {
            if (SoundPlayState.eSS_Play == m_playState)     // ������ڲ���״̬��
            {
                return !m_audio.isPlaying;
            }

            return false;
        }
    }
}