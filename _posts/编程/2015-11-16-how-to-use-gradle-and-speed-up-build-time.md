---
layout: post
title: 使用 Gradle 快速构建项目以及 Gradle 速度优化
categories: [编程]
tags: [Gradle]
published: True

---

## 内容简介

对于一款构建工具来说，首要的使命便是将项目构建起来，然后才是考虑如何加快构建的速度。毕竟在持续集成的开发理念之下，跑`ci`就是程序员日常最经常要做的事情，而等待的过程往往是非常漫长的，甚至于有童鞋专门去买了本字帖，以便于在每次等`ci`的时候打发时间。

这篇文章首先会从如何使用Gradle插件开始，毕竟要先干活，然后进阶到如何写一个自定义Task，以及Incremental Task的原理。当然，最后总结几个可以直接用于加快Gradle构建速度的优化技巧，简单粗暴，立马生效！

## 如何使用Gradle插件

我们在Java项目根目录下会有一个`build.gradle`文件，Gradle的所有配置都可以放在这个文件里面。首先从最基本的Java插件说起，大部分的项目构建流程都是：编译Java源文件，运行单元测试，最终生成一个包含所有class文件的JAR包，而Gradle使用插件的形式来使整个过程自动化，只需要使用`apply plugin: 'java'`，然后就可以通过命令行使用与之相关的Task了：

|Task名称|依赖于|Task类型|描述|
|---------|----------|----|-----------|
|assemble|所有用于项目归档打包的包括jar在内的Task，一些插件可以提供额外的Task。|Task |装配项目中所有已归档的文件。|
|check|项目中包括test在内的所有验证任务，也有一些插件可以提供额外的Task。|Task|执行所有验证任务。|
|build|check（验证检查）和assemble（装配打包）|Task |执行完整的项目构建任务。|

上面的生命周期Tasks都会依赖于其他的基本Task：

![](https://docs.gradle.org/2.1/userguide/img/javaPluginTasks.png)

然后只需要运行`gradle clean build`就会自动执行：（下图为默认的文件目录结构，自定义[戳这里](https://docs.gradle.org/2.1/userguide/java_plugin.html)。）

![](http://gradle.wpengine.netdna-cdn.com/wp-content/uploads/2015/03/project-structure.svg)

当然这里还有很多其他的官方插件或者第三方插件，比如[checkstyle](https://docs.gradle.org/2.1/userguide/checkstyle_plugin.html)和[pact-jvm](https://github.com/DiUS/pact-jvm/tree/master/pact-jvm-provider-gradle)。

最后来一个完整的`build.gradle`示例：

```groovy
apply plugin: 'java'

group = 'org.gradle.example'
version = '1.0.0'
sourceCompatibility = targetCompatibility = 1.7

repositories {
    mavenCentral()
}

dependencies {
    compile 'org.slf4j:slf4j-api:1.7.10'
    runtime 'org.slf4j:slf4j-simple:1.7.10'
    testCompile 'junit:junit:4.12'
}

jar {
    manifest {
        attributes 'Main-Class': "${project.group}.App"
    }
}

task sourceJar(type: Jar) {
    classifier = 'sources'
    from sourceSets.main.allSource
}
```

## 自定义Task

Gradle的一大亮点就是FULLY PROGRAMMABLE BUILDS，你可以将以往的配置和重复动作都使用Groovy脚本自动化管理起来，无限制定制化:

> Conventions derive powerful build logic from a single line of configuration. The build language makes way for unlimited customization, allowing you to adapt Gradle to concisely fit the needs of your organization.

### Hello World!

按照国际惯例先来一个HelloWorld:

    task hello << {
        println 'Hello world!'
    }

    > gradle -q hello
    Hello world!

另外一个常用的语法就是定义Task之间的依赖关系，所依赖的Task会按顺序依次运行：

    task intro(dependsOn: [hello, foo, bar]) << {
        println "I'm Gradle"
    }

    > gradle -q intro
    Hello world!
    I'm Gradle

而与此同时通过命令行还可以排除所依赖的Task，通过`gradle -q tasks`可以显示已经定义的所有Task，当然Task还可以直接使用缩写形式：`compileTest` -> `cT`。

    > gradle intro -x foo bar
    Hello world!
    I'm Gradle

更多关于Task的内容[戳这里](https://docs.gradle.org/current/userguide/more_about_tasks.html)，当构建任务复杂度上升之后，你可以像编程一样分文件来组织不同的任务，以便于管理和设置各自Task的内容属性等，而`if-else`、`class`以及注解都不在话下，它就是[一种Groovy DSL语言](http://www.groovy-lang.org/)。

### Incremental Task

首先在Task里面有一个[up-to-date](https://docs.gradle.org/current/userguide/more_about_tasks.html#sec:up_to_date_checks)的概念，可以自动跳过没有任何更新的Task从而加快构建速度。使用TaskInputs和TaskOutputs属性定义好Task的输入输出文件之后，在第一次运行Task的时候，Gradle会记录input文件内容的Hash值快照，也会记录下Task运行成功之后的output快照。而在这之后，每当Task被执行之前Gradle就会以前所保存的快照进行对比，只有在有差异的情况才会重新执行该Task。

    task generator {
        def fileCount = 10
        inputs.property "fileCount", fileCount
        def generatedFileDir = file("$buildDir/generated")
        outputs.dir generatedFileDir
        doLast {
            println "generating file."
            generatedFileDir.mkdirs()
            for (int i=0; i<fileCount; i++) {
                new File(generatedFileDir, "${i}.txt").text = i
            }
        }
    }

    > gradle generator
    :generator
    generating file.
    # Run again!
    > gradle generator  –info
    Skipping task ‘:generator’ as it is up-to-date (took 0.007 secs).
    :generator UP-TO-DATE

我们还可以定义Task的类型，除了输入和输出之后需要一个带有@TaskAction注解的方法，然后该任务就可以针对out of date的输入文件执行相应的操作，并且对于自上次操作已被删除的输入文件执行单独的动作，更多内容[戳这里](https://docs.gradle.org/current/dsl/org.gradle.api.tasks.incremental.IncrementalTaskInputs.html)。

```groovy
class IncrementalReverseTask extends DefaultTask {
     @InputDirectory
     def File inputDir

     @OutputDirectory
     def File outputDir

     @TaskAction
     void execute(IncrementalTaskInputs inputs) {
         if (!inputs.incremental)
             project.delete(outputDir.listFiles())

         inputs.outOfDate { change ->
             def targetFile = project.file("$outputDir/${change.file.name}")
             targetFile.text = change.file.text.reverse()
         }

         inputs.removed { change ->
             def targetFile = project.file("$outputDir/${change.file.name}")
             if (targetFile.exists()) {
                 targetFile.delete()
             }
         }
     }
 }
```

比如说像`JavaCompile`这样Gradle内置的一些插件都使用Incremental Task的原理，已经定义好了inputs (Java source files)以及outputs (class files)，从而我们就可以在配置使用[增量编译](https://docs.gradle.org/2.1/dsl/org.gradle.api.tasks.compile.JavaCompile.html)这样的功能了：

    apply plugin: 'java'
        compileJava {
            //enable incremental compilation
            options.incremental = true
        }


## 加快Gradle构建速度

0x00. 升级Gradle版本并且使用Wrapper

Gradle Wrapper是由Windows batch脚本以及OS X和Linux的shell脚本共同组成，这就允许你在没有安装Gradle的任意操作系统上都能马上构建自己的项目。在`build.gradle`文件中加入wrapper任务并指定最新的版本，然后运行`gradle wrapper`就可以快速升级了：

    task wrapper(type: Wrapper) {
        gradleVersion = '2.8'
    }

### 0x01. 分析构建报告

「知己知彼方能百战百胜」。首先在执行任务的时候加上`gradle --profile`，就可以记录一些有用的信息并且在`build/reports/profile`目录下生成相应的报告，然后分析到底在哪部分花费了过多的时间，可以细分到具体的Task然后才可以进行优化。

![](https://docs.gradle.org/current/userguide/img/profile.png)

### 0x02. 开始增量编译

上面已经提到了，在Java Compile任务中加入以下配置已进入使用增量编译模式：

    apply plugin: 'java'
    compileJava {
        //enable compilation in a separate daemon process
        options.fork = true

        //enable incremental compilation
        options.incremental = true
    }


### 0x03. 开启并行化和后台进程

    org.gradle.parallel=true
    org.gradle.daemon=true
    org.gradle.jvmargs=-Xms256m -Xmx1024m

与此同时还可以通过命令行参数`--parallel-threads=4`指定并行线程的个数，而在开启过后可以使用`gradlew --stop`停止所有Gradle进程，这也包括了非daemon的进程，那什么是daemon[戳这里](https://docs.gradle.org/current/userguide/gradle_daemon.html)。还可以调整Java虚拟机的参数，这将加快构建本身，解释请看[StackOverflow的答案](http://stackoverflow.com/questions/14763079/what-are-the-xms-and-xmx-parameters-when-starting-jvms/14763095#14763095)。

### 0x04. 使用JCenter而不是Maven Central

请看JCenter的slogn：[Forget about Maven Central](https://bintray.com/bintray/jcenter).

### 0x05. 使用offline模式

通过使用`--profile`生成的报告就可以发现，在构建过程中最大的耗时都在于JavaCompile这个Task，而观察log就发现罪魁祸首就在于resolving dependencies，也就是解析依赖的这一步。一般情况下，Gradle都会将项目依赖缓存在本地中，所以使用`--offline`，就可以让它不再去[联网检查更新](https://discuss.gradle.org/t/is-there-a-true-never-needed-a-network-local-mode-for-gradle/7237)，没必要。

### 0x06. 优化Task内容以及执行顺序

比如说在我们的项目当中有一个asciidoctor的任务是用于将Swagger Test所生成的内容转化为HTML5和PDF文件，这显然在开发的时候并不需要每次都去生成，所以就可以使用`-x`参数去跳过[这个Task](http://www.practicalgradle.org/blog/2010/10/skipping-tasks/)。

    gradlew build -x asciidoctor

与此同时，在跑`ci`（具体内容为`gradlew clean build pactverify`）的时候我们会执行一个pactverify的任务去做Contact Testing，而这个Task需要启动我们真实的应用程序，然后再去验证实实在在的返回值，也就是说依赖于/等待于`gradlew bootRun`这个漫长的Task，而`gradlew bootRun`又是依赖于`graldew build`这个Task的，更可怕的是`graldew build`又依赖于`:compileJava`，结果在没有使用offline模式的情况下，跑`ci`的时间就被整整拖成了将近十分钟，这岂不是等死个人。

所以在`gradlew pactverify`这个任务当中所执行的bootRun任务加上offline模式变成`gradlew bootRun --offline -x build`，因为在跑`ci`的时候早就已经解析过一遍依赖并且`build`过了，所以最终将整个跑`ci`的时间最短控制在一分钟左右。

当然需要注意的一个问题就是不要将`ci`脚本中的`--offline`参数提交到远程的Jenkins服务器上了，因为那台机子还是需要每次都去解析最新的项目依赖。一个技巧就是将`ci`脚本这个文件的修改放在Intellij IDEA的Default文件修改列表中，每次提交代码的时候不选中它就好了。

### 0x07. 进阶：自定义offline模式的Incremental task

既然offline模式所节约的时候非常多，那就可以根据`gradle.properties`中所定义的项目依赖库的版本是否更新，从而增量使用offline模式来连接远程参考解析依赖。

可以通过`gradle.startParameter.setOffline(true)`设置offline模式的参数，参考[这里](https://discuss.gradle.org/t/is-it-possible-to-make-offline-switch-to-default-setting-from-build-gradle/3439)，但是需要学习Groovy语言去定义一个增量任务，暂且就没有深究了。

## 参考资料

这是一个我所收集的有关Gralde内容的[Kifi](https://www.kifi.com)集合，持续更新哟：<https://www.kifi.com/jimmylv/gradle>
