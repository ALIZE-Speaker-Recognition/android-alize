package AlizeSpkRec;

public class SimpleSpkDetSystem
{
    static
    {
        System.loadLibrary("alize-native");
    }

    public SimpleSpkDetSystem(String configFilename, String workdirPath) throws AlizeException
    {
        initSystem(configFilename, workdirPath);
    }

    protected void finalize() throws Throwable {
        releaseSystem();
        super.finalize();
    }


    public native long featureCount() throws AlizeException;
    public native long speakerCount() throws AlizeException;
    public native boolean isUBMLoaded() throws AlizeException;
    public native String[] speakerIDs() throws AlizeException;
    public native void setOption(String name, String value) throws AlizeException;

    public native void addAudio(byte[] data) throws AlizeException;
    public native void addAudio(String filename) throws AlizeException;
    public native void saveAudio(String filename) throws AlizeException;
    public native void resetAudio() throws AlizeException;

    public native void addFeatures(byte[] data) throws AlizeException;
    public native void addFeatures(String filename) throws AlizeException;
    public native void saveFeatures(String filename) throws AlizeException;
    public native void resetFeatures() throws AlizeException;

    public native void loadBackgroundModel(String filename) throws AlizeException;
    public native void loadSpeakerModel(String speakerId, String filename) throws AlizeException;
    public native void saveSpeakerModel(String speakerId, String filename) throws AlizeException;
    public native void removeSpeaker(String speakerId) throws AlizeException;
    public native void removeAllSpeakers() throws AlizeException;
    public native void createSpeakerModel(String speakerId) throws AlizeException;
    public native void adaptSpeakerModel(String speakerId) throws AlizeException;

    public class SpkRecResult
    {
        public boolean match;
        public float score;
        public String speakerId;

        public SpkRecResult() {}
        public SpkRecResult(boolean match, float score, String speakerId) {
            this.match = match;
            this.score = score;
            this.speakerId = speakerId;
        }
    }

    public SpkRecResult verifySpeaker(String targetSpeakerId) throws AlizeException {
        return verifySpeaker(targetSpeakerId, false);
    }
    public SpkRecResult verifySpeaker(String targetSpeakerId, boolean withScoreAccumulation) throws AlizeException {
        SpkRecResult result = new SpkRecResult();
        verifySpeaker(targetSpeakerId, withScoreAccumulation, result);
        return result;
    }
    private native void verifySpeaker(String targetSpeakerId, boolean withScoreAccumulation, SpkRecResult result) throws AlizeException;

    public SpkRecResult identifySpeaker() throws AlizeException {
        return identifySpeaker(false);
    }
    public SpkRecResult identifySpeaker(boolean withScoreAccumulation) throws AlizeException {
        SpkRecResult result = new SpkRecResult();
        identifySpeaker(withScoreAccumulation, result);
        return result;
    }
    public native void identifySpeaker(boolean withScoreAccumulation, SpkRecResult result) throws AlizeException;

    public native void resetAccumulatedScore(String speakerId) throws AlizeException;
    public native void resetAllAccumulatedScores() throws AlizeException;


    private long nativeSystemPtr = 0;
    private native void initSystem(String configFilename, String workdirPath) throws AlizeException;
    private native void releaseSystem();

}