package AlizeSpkRec;

import java.io.*;

public class SimpleSpkDetSystem
{
    static
    {
        System.loadLibrary("alize-native");
    }

    public SimpleSpkDetSystem(InputStream configInput, String workdirPath) throws AlizeException, IOException
    {
        workdir = new File(workdirPath);
        File tmpConfigFile = transferDataToWorkdir(configInput,"config",".cfg");
        initSystem(tmpConfigFile.getName(), workdirPath);
        tmpConfigFile.delete();
    }

    public SimpleSpkDetSystem(String configFilename, String workdirPath) throws AlizeException
    {
        workdir = new File(workdirPath);
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
    public void addAudio(InputStream audio) throws AlizeException, IOException
    {
        File tmpAudioFile = transferDataToWorkdir(audio,"tmp_audio",".audio");
        addAudio(tmpAudioFile.getAbsolutePath());
        tmpAudioFile.delete();
    }
    public native void saveAudio(String filename) throws AlizeException;
    public native void resetAudio() throws AlizeException;

    public native void addFeatures(byte[] data) throws AlizeException;
    public native void addFeatures(String filename) throws AlizeException;
    public void addFeatures(InputStream features) throws AlizeException, IOException
    {
        File tmpFeatureFile = transferDataToWorkdir(features,"tmp_features",".prm");
        addFeatures(tmpFeatureFile.getAbsolutePath());
        tmpFeatureFile.delete();
    }
    public native void saveFeatures(String filename) throws AlizeException;
    public native void resetFeatures() throws AlizeException;

    public native void loadBackgroundModel(String filename) throws AlizeException;
    public void loadBackgroundModel(InputStream model) throws AlizeException, IOException
    {
        File tmpModelFile = transferDataToWorkdir(model,"tmp_world",".gmm");
        loadBackgroundModel(tmpModelFile.getAbsolutePath());
        tmpModelFile.delete();
    }
    public native void loadSpeakerModel(String speakerId, String filename) throws AlizeException;
    public void loadSpeakerModel(String speakerId, InputStream model) throws AlizeException, IOException
    {
        File tmpModelFile = transferDataToWorkdir(model,"tmp_"+speakerId,".gmm");
        loadSpeakerModel(speakerId, tmpModelFile.getAbsolutePath());
        tmpModelFile.delete();
    }
    public native void saveSpeakerModel(String speakerId, String filename) throws AlizeException;
    public native void removeSpeaker(String speakerId) throws AlizeException;
    public native void removeAllSpeakers() throws AlizeException;
    public native void createSpeakerModel(String speakerId) throws AlizeException;
    public native void adaptSpeakerModel(String speakerId) throws AlizeException;

    public static class SpkRecResult
    {
        public boolean match;
        public float score;
        public String speakerId;

        public SpkRecResult() {}
    }

    public SpkRecResult verifySpeaker(String targetSpeakerId) throws AlizeException {
        return verifySpeaker(targetSpeakerId, false);
    }
    private native SpkRecResult verifySpeaker(String targetSpeakerId, boolean withScoreAccumulation) throws AlizeException;

    public SpkRecResult identifySpeaker() throws AlizeException {
        return identifySpeaker(false);
    }
    public native SpkRecResult identifySpeaker(boolean withScoreAccumulation) throws AlizeException;

    public native void resetAccumulatedScore(String speakerId) throws AlizeException;
    public native void resetAllAccumulatedScores() throws AlizeException;


    private long nativeSystemPtr = 0;
    private File workdir;
    private native void initSystem(String configFilename, String workdirPath) throws AlizeException;
    private native void releaseSystem();
    private File transferDataToWorkdir(InputStream dataInput, String prefix, String suffix) throws IOException
    {
        File tmpFile = File.createTempFile(prefix,suffix,workdir);
        OutputStream dataOutput = new BufferedOutputStream(new FileOutputStream(tmpFile));
        int b;
        while ((b = dataInput.read()) != -1)
        {
            dataOutput.write(b);
        }
        dataOutput.close();
        return tmpFile;
    }

}