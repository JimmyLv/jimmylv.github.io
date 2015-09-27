---
layout: 
title: 提高Gradle运行速度
categories: []
tags: []
published: True

---

## how to speed up gradle build time

//Record some useful timing information
--profile

//Enable incremental compilation in java plugin
options.incremental = true

//Reduce total build time for a multi-project build
--parallel / org.gradle.parallel=true 
org.gradle.daemon=true
org.gradle.jvmargs=-Xms256m -Xmx1024m

//create so more process
``gradlew --stop` can kills all gradle processes (even non-daemon)`

//improve workflow
`gradlew bootRun --offline` in pactverify task
`gradlew build` in `gradlew bootRun`
`ass`
`:compileJava` in `graldew build`
`resolve dependices` in `:compileJava`

//waiting for bootRun to start application

//just use jcenter()

//write custom Incremental task in gradle
to judge when we should use offline mode automatically

final solution:
//only use `offline` mode in bootRun in pactverify task

//only resolve when version changed, other case will be ok if you use `gradlew --offline` mannually 