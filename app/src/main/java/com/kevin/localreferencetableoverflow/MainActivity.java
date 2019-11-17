package com.kevin.localreferencetableoverflow;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;
import android.widget.Button;

import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;

public class MainActivity extends AppCompatActivity implements View.OnClickListener {

    private Button btCreateThread;
    private Button btCreateArrayList;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        setTitle(R.string.title);
        btCreateThread = findViewById(R.id.bt_create_thread);
        btCreateArrayList = findViewById(R.id.bt_create_array_list);
        btCreateThread.setOnClickListener(this);
        btCreateArrayList.setOnClickListener(this);
    }

    @Override
    public void onClick(View v) {
        switch (v.getId()) {
            case R.id.bt_create_thread:
                LRTOverflow.createLoopThreadCauseLRTOverflow();
                break;
            case R.id.bt_create_array_list:
                LRTOverflow.createArrayListCauseLRTOverflow();
                break;
        }
    }

    /**
     * 打印所有引用表（局部，全局，弱全局）
     */
    private static void printDumpReferenceTables() {
        try {
            Method dumpHprofDataMethod = getDumpReferenceTablesMethod();
            if (dumpHprofDataMethod != null) {
                dumpHprofDataMethod.invoke(null, new Object[]{});
            }
        } catch (IllegalAccessException | InvocationTargetException e) {
            e.printStackTrace();
        }
    }


    private static Method getDumpReferenceTablesMethod() {
        ClassLoader myLoader = MainActivity.class.getClassLoader();
        Class<?> vmdClass;
        Method meth = null;
        try {
            if (myLoader != null) {
                vmdClass = myLoader.loadClass("dalvik.system.VMDebug");
                try {
                    meth = vmdClass.getMethod("dumpReferenceTables", new Class[]{});
                } catch (NoSuchMethodException nsme) {
                    System.err.println("Found VMDebug but not dumpReferenceTables method");
                    return null;
                }
            }
        } catch (ClassNotFoundException cnfe) {
            return null;
        }
        return meth;
    }
}
