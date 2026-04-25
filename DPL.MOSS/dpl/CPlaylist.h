#pragma once
#define TRACK_MISSING 0xFD
#define TRACK_END 0xFE
#define TRACK_INVALID 0xFF

// static address: 0x6cfd08
// interpretation: CPlaylist* musicPlaylist = (CPlaylist*)0x6cfd08;

struct CPlaylist_TrackFileName {
	int unknown1;
	char m_szName[12];
	
	char __padding0[20];
};

struct CPlaylist_TrackFileNamesHolder {
	CPlaylist_TrackFileName m_tracks[50]; // WARNING: sometimes the actual limit is 48 because of missing songs
};

class CPlaylist {
public:
	char m_TrackCount;
	char m_CurrentTrack;
	char m_Tracks[50];
	CPlaylist_TrackFileNamesHolder* m_TrackFilenames;
	void Shuffle();
};