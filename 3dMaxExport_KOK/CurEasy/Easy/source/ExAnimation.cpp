#include "ExAnimation.h"

namespace EasyOgreExporter
{
	void skeletonKeyframe::exportKeyFrameXml(tinyxml2::XMLElement* keyframesElem, tinyxml2::XMLDocument* pXMLDocument)
	{
		tinyxml2::XMLElement* keyframeElem = pXMLDocument->NewElement("keyframe");
		keyframesElem->InsertEndChild(keyframeElem);

		keyframeElem->SetAttribute("time", time);

		tinyxml2::XMLElement* translateElem = pXMLDocument->NewElement("translate");
		keyframeElem->InsertEndChild(translateElem);

		translateElem->SetAttribute("x", trans.x);
		translateElem->SetAttribute("y", trans.y);
		translateElem->SetAttribute("z", trans.z);

		tinyxml2::XMLElement* rotateElem = pXMLDocument->NewElement("rotateElem");
		keyframeElem->InsertEndChild(rotateElem);

		rotateElem->SetAttribute("angle", rot.w);

		tinyxml2::XMLElement* axisElem = pXMLDocument->NewElement("axis");
		rotateElem->InsertEndChild(axisElem);

		axisElem->SetAttribute("x", rot.x);
		axisElem->SetAttribute("y", rot.y);
		axisElem->SetAttribute("z", rot.z);
	}

	void ExTrack::exportTrackXml(tinyxml2::XMLElement* tracksElem, tinyxml2::XMLDocument* pXMLDocument)
	{
		tinyxml2::XMLElement* trackElem = pXMLDocument->NewElement("track");
		tracksElem->InsertEndChild(trackElem);

		trackElem->SetAttribute("bone", m_bone.c_str());

		tinyxml2::XMLElement* keyframesElem = pXMLDocument->NewElement("keyframes");
		trackElem->InsertEndChild(keyframesElem);

		std::vector<skeletonKeyframe>::iterator keyFrameBeginIte, keyFrameEndIte;
		keyFrameBeginIte = m_skeletonKeyframes.begin();
		keyFrameEndIte = m_skeletonKeyframes.end();

		for (; keyFrameBeginIte != keyFrameEndIte; ++keyFrameBeginIte)
		{
			keyFrameBeginIte->exportKeyFrameXml(keyframesElem, pXMLDocument);
		}
	}

	void ExAnimation::exportAnimationXml(tinyxml2::XMLElement* animationsElem, tinyxml2::XMLDocument* pXMLDocument)
	{
		tinyxml2::XMLElement* animationElem = pXMLDocument->NewElement("animation");
		animationsElem->InsertEndChild(animationElem);

		animationsElem->SetAttribute("name", m_name.c_str());
		animationsElem->SetAttribute("length", m_length);

		tinyxml2::XMLElement* tracksElem = pXMLDocument->NewElement("tracks");
		animationElem->InsertEndChild(tracksElem);

		std::vector<ExTrack>::iterator trackBeginIte, trackEndIte;
		trackBeginIte = m_tracks.begin();
		trackEndIte = m_tracks.end();

		for (; trackBeginIte != trackEndIte; ++trackBeginIte)
		{
			trackBeginIte->exportTrackXml(tracksElem, pXMLDocument);
		}
	}
}