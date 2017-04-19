---
layout: post
title: 【译】使用Spring Boot开发RESTful Web服务
categories: [翻译]
tags: [RESTful, Spring]
published: True

---

# 使用Spring Boot开发RESTful Web服务

原文地址：[Developing a RESTful Web Service Using Spring Boot](http://kielczewski.eu/2014/04/developing-restful-web-service-with-spring-boot/)

Tag: [Spring](http://kielczewski.eu/tag/Spring/), [Spring Boot](http://kielczewski.eu/tag/Spring%20Boot/), [Spring MVC](http://kielczewski.eu/tag/Spring%20MVC/), [JPA](http://kielczewski.eu/tag/JPA/), [Spring Data JPA](http://kielczewski.eu/tag/Spring%20Data%20JPA/), [TDD](http://kielczewski.eu/tag/TDD/)

> I'm really impressed with [Spring Boot](http://projects.spring.io/spring-boot/). Its main goal is to take away most of this boilerplate configuration that was needed before and to replace it with some sensible defaults. One might say it's taking the control away from the developer and giving it to the army of fairies. That's probably right, but in this case the fairies are here to help, and moreover they can easily be cast away from doing particular thing. It's just a matter of doing it yourself as before, and thanks to `@ConditionalOn...` behaviour Spring Boot's auto configuration will not fire up.

我对[Spring Boot](http://projects.spring.io/spring-boot/)的印象非常深刻。它的主要目的就是为了减少以往所需要的大部分初始化配置，从而采用一些默认的设置来代替。可能有人会说，这将会使开发者失去控制，而将控制权让给了一些黑暗魔法。这可能是正确的，但在这种情况下，仙子却是来帮忙的，而且他们也可以很容易得从这些特定的事情脱离开来。它只是像以往一样，做你亲历而为的那些事情，与此同时，通过`@ConditionalOn...`可以设置Spring Boot的自动配置的启动。

> In the following article I will explore the way of employing Spring Boot to create a very basic, restful web service. As usual the source code can be found [here on GitHub](https://github.com/bkielczewski/example-spring-boot-rest) to play around. 

在接下来的文章里，我将会尝试使用Spring Boot，来创建一个基本的RESTful Web服务。像往常一样，源代码放在[GitHub](https://github.com/bkielczewski/example-spring-boot-rest)上。

## Service overview | 服务概述

> The goal will be to create a simple web service with the following requirements:

目标就是构建一个简单的web服务，需求如下：

> * Given no user with same id exists, it should store a new user in the database and immediately return the stored object.
    - 给一个具有ID的不存在的用户，这将在数据库中存储一个新的用户，并立即返回存储的对象。
> * Given there exists a user with same id, it should not store, but return error status with the message.
    - 给一个具有ID的已存在的用户，将不会存储，而是返回错误码信息。
> * Given there are previously stored users, it should be able to retrieve the list of them.
    - 给定已存储的用户，将拿到用户的列表。

## Maven

> Let's start with creating a `pom.xml`.

让我们从创建`pom.xml`开始。

```xml
 <project xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xmlns="http://maven.apache.org/POM/4.0.0"
          xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 http://maven.apache.org/maven-v4_0_0.xsd">
     <modelVersion>4.0.0</modelVersion>

     <groupId>eu.kielczewski.example.spring</groupId>
     <artifactId>example-spring-boot-rest</artifactId>
     <version>1.0-SNAPSHOT</version>
     <packaging>jar</packaging>

     <parent>
         <groupId>org.springframework.boot</groupId>
         <artifactId>spring-boot-starter-parent</artifactId>
         <version>1.0.1.RELEASE</version>
     </parent>

     <name>Example Spring Boot REST Service</name>

     <properties>
         <java.version>1.7</java.version>
         <guava.version>16.0.1</guava.version>
         <project.build.sourceEncoding>UTF-8</project.build.sourceEncoding>
         <project.reporting.outputEncoding>UTF-8</project.reporting.outputEncoding>
     </properties>

 </project>
```

> The relevant thing here is `<parent>` tag - we will be inheriting from Spring Boot's parent POM. It's not absolutely necessary, however it provides a very useful thing which is the dependency management. It has already defined many artifacts we might find useful to use, together with their recent versions supported by Spring, so it really saves up the hassle of tracking them down yourself. We just need to override `java.version` property, which defaults to 1.6, and add version property for [Guava](https://code.google.com/p/guava-libraries/), which is a nice thing to have in handy - but both of these are a matter of personal preference.

需要关注的就是`<parent>`标签——我们将会继承Spring Boot父类的POM。当然这不是必须的，但是这有一个非常有用的好处就是依赖管理。它已经帮我们定义了可能会用到的很多有用的东西，而且都是可以被Spring支持的最新版本，所以真的是解决了很多需要自己搜寻的麻烦事。我们需要重写`java.version`属性，默认是1.6，然后添加[Guava](https://code.google.com/p/guava-libraries/)版本信息，这都是一些非常好用的东西。——但这纯属个人喜好。

> Next thing to do will be to specify the dependencies, which will decide upon the technology stack we will be using:

下一件事就是指定我们将会用到的技术栈依赖：

```xml
<dependencies>

    <!-- Spring Boot -->

    <dependency>
        <groupId>org.springframework.boot</groupId>
        <artifactId>spring-boot-starter</artifactId>
    </dependency>

    <dependency>
        <groupId>org.springframework.boot</groupId>
        <artifactId>spring-boot-starter-test</artifactId>
        <scope>test</scope>
    </dependency>

    <dependency>
        <groupId>org.springframework.boot</groupId>
        <artifactId>spring-boot-starter-web</artifactId>
    </dependency>

    <dependency>
        <groupId>org.springframework.boot</groupId>
        <artifactId>spring-boot-starter-data-jpa</artifactId>
    </dependency>

    <!-- Hibernate validator -->

    <dependency>
        <groupId>org.hibernate</groupId>
        <artifactId>hibernate-validator</artifactId>
    </dependency>

    <!-- HSQLDB -->

    <dependency>
        <groupId>org.hsqldb</groupId>
        <artifactId>hsqldb</artifactId>
        <scope>runtime</scope>
    </dependency>

    <!-- Guava -->

    <dependency>
        <groupId>com.google.guava</groupId>
        <artifactId>guava</artifactId>
        <version>${guava.version}</version>
    </dependency>

    <!-- Java EE -->

    <dependency>
        <groupId>javax.inject</groupId>
        <artifactId>javax.inject</artifactId>
        <version>1</version>
    </dependency>

</dependencies>
```

> When it comes to Spring Boot its functions are spread between the starter modules. The `spring-boot-starter` is the main one, followed by `spring-boot-starter-test` which pulls some nice tools for unit testing including JUnit4 and Mockito. Next comes `spring-boot-starter-web` that pulls Spring MVC dependencies, but also Jackson which will be used for JSON, and most importantly Tomcat, which act as embedded Servlet container. Finally `spring-boot-starter-data-jpa` which is responsible for setting up Spring Data JPA, and comes bundled with Hibernate.

当涉及到Spring Boot的时候，它的功能就是连接各个starter模块。最主要的就是`spring-boot-starter`，然后是`spring-boot-starter-test`，包含了一些非常好用的单元测试工具，比如JUnit4和Mockito。接下来就是`spring-boot-starter-web`，包含了Spring MVC的相关依赖，Jackson将在JSON数据结构中用到。最重要单独的就是Tomcat，它将作为一个内嵌的Servlet容器。最后就是`spring-boot-starter-data-jpa`，用来设置Spring Data JPA，和Hibernate绑定在一起。

> Additional dependencies include Hibernate Validator, as we will be doing some validation. HSQLDB will be the database engine, chosen here because it can be easily embedded and has in memory database feature which is handy for tutorial purposes. Notice I haven't specified versions for these - they are managed by `spring-boot-starter-parent`.

额外的依赖还包括Hibernate Validator，因为我们将会有一些数据验证。我们选用HSQLDB作为数据库引擎，因为它很容易被嵌入本项目，而且内存数据库的特性也对本教程的目标非常有用。需要注意的是，我并没有特意指定它们的版本，这些都会被`spring-boot-starter-parent`所管理。

> The rest is something of my personal preference - Guava, because it's cool ;) and JSR-330 API to replace `@Autowired` annotation with `@Inject`, which I like better.

剩下的纯属我的个人爱好——Guava，因为它非常之酷！JSR-330的API可以将`@Autowired`注解替换成我更喜欢的`@Inject`。

> Last thing that's left is to add Spring Boot Maven Plugin:

最后一件事情就是Spring Boot的Maven插件。

```xml
<build>
    <plugins>

        <!-- Spring Boot Maven -->

        <plugin>
            <groupId>org.springframework.boot</groupId>
            <artifactId>spring-boot-maven-plugin</artifactId>
        </plugin>

    </plugins>
</build>
```

> This plugin does two things:

这个插件做了两件事：

> * It provides spring-boot:run goal for Maven, so the application can be easily run without packaging.
    - 为Maven提供了spring-boot:run命令，所以应用不用打包就可以轻松运行。
> * It hooks into `package` goal to produce executable JAR file with all the dependencies included, similar to maven-shade-plugin, but in less messy way.
    - 同时也提供了`package`命令，可以将所有依赖打包到一个可执行的JAR文件中，和maven-shade-plugin很像，但是采取的方式更加简洁。

## Writing the main() method | 编写 main() 方法

> The execution will start by firing up the main() method, so let's write a class to hold it:

程序执行需要一个main()方法，所以让我们写一个类包含它：

```java
@Configuration
@EnableAutoConfiguration
@ComponentScan
public class Application extends SpringBootServletInitializer {

    public static void main(final String[] args) {
        SpringApplication.run(Application.class, args);
    }

    @Override
    protected final SpringApplicationBuilder configure(final SpringApplicationBuilder application) {
        return application.sources(Application.class);
    }
}
```

> This class has the following features:

这个类有如下特性：

>   * It acts as a `@Configuration` class for Spring.
      - `@Configuration`表示这是一个Spring的类
>   * As such it has `@ComponentScan` annotation that enables scanning for another Spring components in current package and its subpackages.
      - 同样地，`@ComponentScan`注解可以从当前package和子package中自动加载其他的Spring组件。
>   * Another annotation is `@EnableAutoConfiguration` which tells Spring Boot to run autoconfiguration.
      - 另外一个注解就是`@EnableAutoConfiguration`，告诉Spring Boot采用自动配置。
>   * It also extends `SpringBootServletInitializer` which will configure Spring servlet for us, and overrides the `configure()` method to point to itself, so Spring can find the main configuration.
      - 这个类还继承了`SpringBootServletInitializer`，这就帮我们配置了Spring Servlet，重写`configure()`方法指向自己，Spring就可以自动配置了。
>   * Finally, the `main()` method consists of single static call to `SpringApplication.run()`.
      - 最后，`main()`方法直接调用了`SpringApplication.run()`静态方法。

> At this point this is all that is required to configure the application, so we can start implementing.

这就是我们这个应用程序的所有配置了，下面我们开始实现。

## Adding UserController | 添加 UserController

> Let's start with writing a test case for creating a new user through the UserController.

让我们从一个测试案例开始，通过UserController来创建一个新用户。

```java
@RunWith(MockitoJUnitRunner.class)
public class UserControllerTest {

    @Mock
    private UserService userService;

    private UserController userController;

    @Before
    public void setUp() {
        userController = new UserController(userService);
    }

    @Test
    public void shouldCreateUser() throws Exception {
        final User savedUser = stubServiceToReturnStoredUser();
        final User user = new User();
        User returnedUser = userController.createUser(user);
        // verify user was passed to UserService
        verify(userService, times(1)).save(user);
        assertEquals("Returned user should come from the service", savedUser, returnedUser);
    }

    private User stubServiceToReturnStoredUser() {
        final User user = new User();
        when(userService.save(any(User.class))).thenReturn(user);
        return user;
    }

}
```

> From this test case we see that in order to create a new user, we need to have `UserController` with `createUser()` method, that takes the `User` object and passes it to the `UserService`, that will be responsible for doing the actual work.

从这个测试中我们可以看到，为了创建新用户，我们需要有一个`UserController`的`createUser()`方法，它将`User`对象传入`UserService`，然后进行实际的操作。

> Both `MockitoJUnitRunner.class` and `@Mock` annotation come from Mockito and their purpose is to inject mocked object instead of real implementation of UserService interface. Thanks to this, without the need for a real implementation of `UserService`, I can simulate returning a stored `User` object that comes from the service and verify that it will be exactly the object the `UserController` is going to return. I also check that the `UserService` is going to be called exactly once.

`MockitoJUnitRunner.class`和`@Mock`注解都来自于Mockito，用于注入已经Mock的对象，就不用实现真正的`UserService`了。我可以模拟从Service返回一个已经存储的`User`对象，然后验证它是否是`UserController`将要返回的那个对象，同时验证`UserService`是否被调用过一次。

> From the REST point of view it will hook up to the POST http method of the `/user` resource.

从REST的角度来说，它将会和`/user` resource的POST方法联系起来。

> So let's implement it:
    
所以让我们来实现它：

```java
@RestController
public class UserController {

    private final UserService userService;

    @Inject
    public UserController(final UserService userService) {
        this.userService = userService;
    }

    @RequestMapping(value = "/user", method = RequestMethod.POST)
    public User createUser(@RequestBody @Valid final User user) {
        return userService.save(user);
    }

}
```

> Points to notice:

注意以下几点：

>   * It's annotated with `@RestController`. The difference between this and `@Controller` annotation is the former also implies `@ResponseBody` on every method, which means there is less to write since from a RESTful web service we are returning JSON objects anyway.
      - `@RestController`注解和`@Controller`的不同就在，前者会将`@ResponseBody`传到每个方法，这就意味着可以少写一些代码，因为我们总是会从RESTful的Web Service返回JSON对象。
>   * `@RequestMapping` maps the `createUser()` to the POST request on the `/user` url.
      - `@RequestMapping`里的值表示`createUser()`方法的url是`/user`，请求方法为POST。
>   * Method takes the `User` object as a parameter. It is created from the body of the request thanks to `@RequestBody` annotation. It is then validated, which is enforced by `@Valid`.
      - 这个方法将`User`对象作为参数，通过`@RequestBody`注解可以从request body中拿出来并且创建对象，`@Valid`表示它会被验证。
>   * The `UserService` will be injected to the constructor, and `User` object is passed to its `save()` method for storage.
      - `UserService`将会被注入到构造函数中，`User`对象将被传到`save()`方法中保存。
>   * After storing, the stored `User` object will be returned. Spring will convert it back to JSON automatically, even without `@ResponseBody` annotation which is default for `@RestController`.
      - `User`对象在保存之后就会被返回，Spring将会将其自动转成JSON，哪怕没有`@ResponseBody`，这是`@RestController`的功能。

> How about UserService and User then? For the test to pass we need only an interface for UserService, because it is not even created, but merely mocked. It should take `User` objects into the `save()` methods which will be used to save them, then it should return saved `User` object back to the caller.

对测试来说，只需要传一个UserService的接口即可，因为它可以被Mock而并不用真正创建出来。接下来，UserService应该把`User`对象传入`save()`方法中保存起来，然后将`User`对象返回给调用者。

```java
public interface UserService {

    User save(User user);

}
```

> As for `User` object it can be anything at this stage, for example:

至于`User`对象，在这个阶段它可以是任何东西，比如：

```java
public class User {

    @NotNull
    @Size(max = 64)
    private String id;

    @NotNull
    @Size(max = 64)
    private String password;

    // getters

}
```

> Where `@NotNull` and `@Size` are validation constraints the object will be checked against while being deserialized from the request body.

`@NotNull`和`@Size`就是验证对象的一些限制，它将会检查从request请求中反序列化出来的对象内容。

## Adding UserService | 添加 UserService

> Having an interface for `UserService` it would be useful to have an implementation of this `save()` method to do the work for us. Let's start with the test case to see how it might work:

实现`UserService`接口的`save()`方法将会很有用，让我们从测试开始，看它是如何工作的：

```java
@RunWith(MockitoJUnitRunner.class)
public class UserServiceImplTest {

    @Mock
    private UserRepository userRepository;

    private UserService userService;

    @Before
    public void setUp() {
        userService = new UserServiceImpl(userRepository);
    }

    @Test
    public void shouldSaveNewUser() {
        final User savedUser = stubRepositoryToReturnUserOnSave();
        final User user = new User();
        final User returnedUser = userService.save(user);
        // verify repository was called with user
        verify(userRepository, times(1)).save(user);
        assertEquals("Returned user should come from the repository", savedUser, returnedUser);
    }

    private User stubRepositoryToReturnUserOnSave() {
        User user = new User();
        when(userRepository.save(any(User.class))).thenReturn(user);
        return user;
    }

}
```

> The assumption is that the `UserService` will delegate actual storage to the `UserRepository`, which is mocked, and later stubbed to return a stored `User` object. Then I'm checking whether the object returned from `save()` is the stored one, and that `UserRepository` is called exactly once.

假设`UserService`将会使用`UserRepository`来进行实际的数据存储，首先将它Mock，然后Stub返回一个已存储的`User`对象。然后我就可以验证从`save()`返回回来的对象是否就是被存储的那个`User`，还有就是`UserRepository`有没有被实际调用一次。

> As previously, at this point all we need is the interface for `UserRepository`, but thanks to Spring Data JPA it's also everything that we'll ever need for this project. The interface looks like this:
    
像以前一样，我们需要做的就是一个`UserRepository`接口。而多亏了Spring Data JPA，已经为我们准备了项目所需要的所有东西。接口就像这样：

```java
public interface UserRepository extends JpaRepository<User, String> {

}
```

> It just extends `JpaRepository` generic interface with `User` and `String` as type parameters. The former indicates that there will be `User` objects in this repository, latter that it's primary key will be of the `String` type. The `save()` method we need is already there inherited, among other basic CRUD methods.

只需要继承`JpaRepository`接口，将`User`和`String`作为类型参数就可以了。前者意味着将被存储到repository的是一个`User`对象，后者表示primary key是`String`类型。

> We won't need to implement this interface, because that's how Spring Data JPA works - it generates the implementation for us.

我们不需要实现这个接口，因为这就是Spring Data JPA的作用——直接就为我们实现好了。

> We need however to make the test to pass by implementing `UserService`:

然后我们实现`UserService`就可以让测试通过了：

```java
@Service
public class UserServiceImpl implements UserService {

    private final UserRepository repository;

    @Inject
    public UserServiceImpl(final UserRepository repository) {
        this.repository = repository;
    }

    @Override
    @Transactional
    public User save(final User user) {
        return repository.save(user);
    }

}
```

> It's a real simple implementation. Thing to notice is `@Transactional` annotation, that starts the transaction when the method is called as we are going to change the database by inserting a new `User`.

这就是一个非常简单的实现，需要注意的是`@Transactional`注解，当这个方法被调用的时候就会开始进行数据处理，因为我们会改变数据库，插入一个新的`User`。

> Now the test should pass, but we are inserting `User` object into the database so it needs to be made a proper `@Entity`:

现在所有的测试都应该过了，但是由于我们正在往数据库插入`User`对象，所以需要加上一个`@Entity`注解。

```java
@Entity
public class User {

    @Id
    @Column(name = "id", nullable = false, updatable = false)
    @NotNull
    @Size(max = 64)
    private String id;

    @Column(name = "password", nullable = false)
    @NotNull
    @Size(max = 64)
    private String password;

    // getters

}
```    

> Notice the `@Entity`, `@Column`, and `@Id` annotations that appeared. The first one tells the object is a JPA entity. The second tells JPA how fields should be mapped to a column and what can be done with them - what the column name will be, whether it's allowed for a column to be updated or have null value. Whereas the `@Id` indicates a primary key for database record - it needs to be non null and unique, so our `User.id` fits here perfectly.

注意`@Entity`、`@Column`和`@Id`注解，第一个表示这个对象是一个JPA Entity，第二个就是告诉JPA要如何将这些字段map到数据库里的每一列以及需要map的内容，比如每一列的名字和是否允许修改，还有就是是否可以为空。`@Id`注解就表示数据库所记录的primary key，这个字段不能为空，而且必须是唯一的，这样我们的`User.id`就完全无可挑剔了。

## Getting this to work | 让它跑起来

> It's now possible to run and test the whole thing. Type:
    
现在就可以运行和测试整个程序了，输入：

```bash
mvn spring-boot:run
```

> And you should have the web service running on the default port from the current compiled sources.

然后你就应该可以编译和运行这个Web Service了，运行在一个默认的端口。

> Alternatively you can build and run the package:

当然你也可以build和运行这个包：

```bash
mvn package
java -jar target/example-spring-boot-rest-1.0-SNAPSHOT.jar
```

> Having done that now you can:

然后就可以：

```bash
curl -X POST -d '{ "id": "test_id", "password": "test_password" }' http://localhost:8080/user
```

> And see whether the response from <http://localhost:8080/> will be like:

然后看看从<http://localhost:8080/>返回的内容：

```json
{ "id": "test_id", "password": "test_password" }
```    

> Which should be our inserted object.

这就是我们之前所插入的那个对象。

## Checking for duplicate Users | 检查重复的 Users

> Another requirement for our service is to prevent inserting users if another user already exists with the same id.

另外一个需求就是，我们的Service能禁止插入已存在相同ID的用户。

> Lets add a test case to the `UserServiceTest`:

给`UserServiceTest`添加新的测试案例：

```java
@Test
public void shouldSaveNewUser_GivenThereExistsOneWithTheSameId_ThenTheExceptionShouldBeThrown() throws Exception {
    stubRepositoryToReturnExistingUser();
    try {
        userService.save(UserUtil.createUser());
        fail("Expected exception");
    } catch (UserAlreadyExistsException ignored) {
    }
    verify(userRepository, never()).save(any(User.class));
}

private void stubRepositoryToReturnExistingUser() {
    final User user = UserUtil.createUser();
    when(userRepository.findOne(user.getId())).thenReturn(user);
}
```

> That assumes we will ask `UserRepository` about existing user with the same id by calling its `findOne()` method. If such user will be found, the `UserAlreadyExistsException` should be thrown, and the `save()` method on the repository should never be called.

假设我们通过相同id调用`UserRepository`的`findOne()`方法来查找已存在的用户。如果有用户被找到，那么将会抛出`UserAlreadyExistsException`异常，`save()`也就不会被调用了。

> Now we need to change `save()` method in `UserService` implementation, that becomes:

现在我们就需要在`UserService`中修改`save()`方法，变成：

```java
@Override
@Transactional
public User save(final User user) {
    User existing = repository.findOne(user.getId());
    if (existing != null) {
        throw new UserAlreadyExistsException(
                String.format("There already exists a user with id=%s", user.getId()));
    }
    return repository.save(user);
}
``` 

> It clearly has the logic the test requires. The `findOne(id)` method already exists in `UserRepository` and returns null if no object could be found.

测试所需要的逻辑非常清晰，如果没有找到相应的对象，存在于`UserRepository`的`findOne(id)`方法就会返回null。

> The web service will be working fine after that, but once `UserAlreadyExistsException` will be thrown, it will cause INTERNAL SERVER ERROR response for the client using it. We should make sure the response will be different, so the client can more clearly see the situation occurred.

完成这些，这个Web Service就可以正常工作了。但是一旦抛出`UserAlreadyExistsException`，它将会向客户端返回`INTERNAL SERVER ERROR`。我们应该确保这种response是不一样的，所以客户端才可以比较清晰得知道发生了什么。

> Let's say it should be a response with CONFLICT status with a meaningful error message in the body. To do that we need to add `@ExceptionHandler` to the `UserController`:

让我们返回一个`CONFLICT`状态码和一个有意义的Error信息，给`UserController`加上`@ExceptionHandler`：

```java
    @ExceptionHandler
    @ResponseStatus(HttpStatus.CONFLICT)
    public String handleUserAlreadyExistsException(UserAlreadyExistsException e) {
        return e.getMessage();
    }
```

> It's just a method that intercepts `UserAlreadyExistsException`, returns its message and sets the response status to CONFLICT.

这就是一个捕获`UserAlreadyExistsException`异常的方法，会返回错误信息和`CONFLICT`状态码。

## Closing remarks | 结束语

> I hope that was helpful to get a grasp on what it takes to do a simple web service the Spring Boot way. The implementation of the third requirement about returning all stored users could be a way to spend an evening instead of doing all the things normal people usually do on evenings. If not, take a peek at the [source code](https://github.com/bkielczewski/example-spring-boot-rest) I have prepared sacrificing mine for you.

我希望这篇文章可以对你有所作用，帮助你理解如何使用Spring Boot创建一个简单的Web Service。第三个关于如何实现返回所有已保存用户的需求，你可以花上一个晚上去完成它，而不是像其他人一样过一个平淡的夜晚。如果没有的话，我已经为你准备好了[源代码](https://github.com/bkielczewski/example-spring-boot-rest)，尽情品尝。
