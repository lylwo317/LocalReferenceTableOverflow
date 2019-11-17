package com.kevin.localreferencetableoverflow;

import java.util.ArrayList;

/**
 * Created by XieJiaHua on 19-11-16.
 */
public class LRTOverflow {

    static {
        System.loadLibrary("lrtoverflow");
    }

    public static native void createLoopThreadCauseLRTOverflow();

    public static native ArrayList<String> createArrayListCauseLRTOverflow();
}
