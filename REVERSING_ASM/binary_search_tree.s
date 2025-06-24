
binary_search_tree.o:     file format elf64-x86-64


Disassembly of section .text:

0000000000000000 <BstCreate>:
   0:	f3 0f 1e fa          	endbr64 
   4:	55                   	push   %rbp
   5:	48 89 e5             	mov    %rsp,%rbp
   8:	48 83 ec 20          	sub    $0x20,%rsp
   c:	48 89 7d e8          	mov    %rdi,-0x18(%rbp)
  10:	bf 20 00 00 00       	mov    $0x20,%edi
  15:	e8 00 00 00 00       	call   1a <BstCreate+0x1a>
  1a:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
  1e:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  22:	48 c7 00 00 00 00 00 	movq   $0x0,(%rax)
  29:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  2d:	48 c7 40 08 00 00 00 	movq   $0x0,0x8(%rax)
  34:	00 
  35:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  39:	48 c7 40 10 00 00 00 	movq   $0x0,0x10(%rax)
  40:	00 
  41:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  45:	48 8b 55 e8          	mov    -0x18(%rbp),%rdx
  49:	48 89 50 18          	mov    %rdx,0x18(%rax)
  4d:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  51:	c9                   	leave  
  52:	c3                   	ret    

0000000000000053 <BstDestroy>:
  53:	f3 0f 1e fa          	endbr64 
  57:	55                   	push   %rbp
  58:	48 89 e5             	mov    %rsp,%rbp
  5b:	48 83 ec 10          	sub    $0x10,%rsp
  5f:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  63:	48 83 7d f8 00       	cmpq   $0x0,-0x8(%rbp)
  68:	0f 84 80 00 00 00    	je     ee <BstDestroy+0x9b>
  6e:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  72:	48 8b 40 08          	mov    0x8(%rax),%rax
  76:	48 85 c0             	test   %rax,%rax
  79:	74 0d                	je     88 <BstDestroy+0x35>
  7b:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  7f:	48 8b 40 10          	mov    0x10(%rax),%rax
  83:	48 85 c0             	test   %rax,%rax
  86:	75 30                	jne    b8 <BstDestroy+0x65>
  88:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  8c:	48 8b 40 08          	mov    0x8(%rax),%rax
  90:	48 85 c0             	test   %rax,%rax
  93:	75 5c                	jne    f1 <BstDestroy+0x9e>
  95:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  99:	48 8b 40 10          	mov    0x10(%rax),%rax
  9d:	48 85 c0             	test   %rax,%rax
  a0:	75 4f                	jne    f1 <BstDestroy+0x9e>
  a2:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  a6:	48 89 c7             	mov    %rax,%rdi
  a9:	e8 00 00 00 00       	call   ae <BstDestroy+0x5b>
  ae:	48 c7 45 f8 00 00 00 	movq   $0x0,-0x8(%rbp)
  b5:	00 
  b6:	eb 3a                	jmp    f2 <BstDestroy+0x9f>
  b8:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  bc:	48 8b 40 08          	mov    0x8(%rax),%rax
  c0:	48 89 c7             	mov    %rax,%rdi
  c3:	e8 00 00 00 00       	call   c8 <BstDestroy+0x75>
  c8:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  cc:	48 8b 40 10          	mov    0x10(%rax),%rax
  d0:	48 89 c7             	mov    %rax,%rdi
  d3:	e8 00 00 00 00       	call   d8 <BstDestroy+0x85>
  d8:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  dc:	48 89 c7             	mov    %rax,%rdi
  df:	e8 00 00 00 00       	call   e4 <BstDestroy+0x91>
  e4:	48 c7 45 f8 00 00 00 	movq   $0x0,-0x8(%rbp)
  eb:	00 
  ec:	eb 04                	jmp    f2 <BstDestroy+0x9f>
  ee:	90                   	nop
  ef:	eb 01                	jmp    f2 <BstDestroy+0x9f>
  f1:	90                   	nop
  f2:	c9                   	leave  
  f3:	c3                   	ret    

00000000000000f4 <BstRemove>:
  f4:	f3 0f 1e fa          	endbr64 
  f8:	55                   	push   %rbp
  f9:	48 89 e5             	mov    %rsp,%rbp
  fc:	48 83 ec 30          	sub    $0x30,%rsp
 100:	48 89 7d d8          	mov    %rdi,-0x28(%rbp)
 104:	48 89 75 d0          	mov    %rsi,-0x30(%rbp)
 108:	48 8b 55 d0          	mov    -0x30(%rbp),%rdx
 10c:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
 110:	48 89 d6             	mov    %rdx,%rsi
 113:	48 89 c7             	mov    %rax,%rdi
 116:	e8 00 00 00 00       	call   11b <BstRemove+0x27>
 11b:	48 89 45 f0          	mov    %rax,-0x10(%rbp)
 11f:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
 123:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
 127:	c7 45 ec 01 00 00 00 	movl   $0x1,-0x14(%rbp)
 12e:	48 83 7d f0 00       	cmpq   $0x0,-0x10(%rbp)
 133:	0f 84 83 00 00 00    	je     1bc <BstRemove+0xc8>
 139:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
 13d:	48 8b 40 10          	mov    0x10(%rax),%rax
 141:	48 85 c0             	test   %rax,%rax
 144:	75 19                	jne    15f <BstRemove+0x6b>
 146:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
 14a:	48 8b 40 08          	mov    0x8(%rax),%rax
 14e:	8b 55 ec             	mov    -0x14(%rbp),%edx
 151:	89 d6                	mov    %edx,%esi
 153:	48 89 c7             	mov    %rax,%rdi
 156:	e8 00 00 00 00       	call   15b <BstRemove+0x67>
 15b:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
 15f:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
 163:	48 8b 40 10          	mov    0x10(%rax),%rax
 167:	be 00 00 00 00       	mov    $0x0,%esi
 16c:	48 89 c7             	mov    %rax,%rdi
 16f:	e8 00 00 00 00       	call   174 <BstRemove+0x80>
 174:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
 178:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
 17c:	48 8b 10             	mov    (%rax),%rdx
 17f:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
 183:	48 89 10             	mov    %rdx,(%rax)
 186:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
 18a:	48 8b 50 08          	mov    0x8(%rax),%rdx
 18e:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
 192:	48 89 50 08          	mov    %rdx,0x8(%rax)
 196:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
 19a:	48 8b 50 10          	mov    0x10(%rax),%rdx
 19e:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
 1a2:	48 89 50 10          	mov    %rdx,0x10(%rax)
 1a6:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
 1aa:	48 89 c7             	mov    %rax,%rdi
 1ad:	e8 00 00 00 00       	call   1b2 <BstRemove+0xbe>
 1b2:	48 c7 45 f8 00 00 00 	movq   $0x0,-0x8(%rbp)
 1b9:	00 
 1ba:	eb 01                	jmp    1bd <BstRemove+0xc9>
 1bc:	90                   	nop
 1bd:	c9                   	leave  
 1be:	c3                   	ret    

00000000000001bf <BstInsert>:
 1bf:	f3 0f 1e fa          	endbr64 
 1c3:	55                   	push   %rbp
 1c4:	48 89 e5             	mov    %rsp,%rbp
 1c7:	48 83 ec 10          	sub    $0x10,%rsp
 1cb:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
 1cf:	48 89 75 f0          	mov    %rsi,-0x10(%rbp)
 1d3:	48 8b 55 f0          	mov    -0x10(%rbp),%rdx
 1d7:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
 1db:	48 89 d6             	mov    %rdx,%rsi
 1de:	48 89 c7             	mov    %rax,%rdi
 1e1:	e8 00 00 00 00       	call   1e6 <BstInsert+0x27>
 1e6:	48 85 c0             	test   %rax,%rax
 1e9:	74 0a                	je     1f5 <BstInsert+0x36>
 1eb:	b8 03 00 00 00       	mov    $0x3,%eax
 1f0:	e9 03 01 00 00       	jmp    2f8 <BstInsert+0x139>
 1f5:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
 1f9:	48 8b 00             	mov    (%rax),%rax
 1fc:	48 85 c0             	test   %rax,%rax
 1ff:	75 15                	jne    216 <BstInsert+0x57>
 201:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
 205:	48 8b 55 f0          	mov    -0x10(%rbp),%rdx
 209:	48 89 10             	mov    %rdx,(%rax)
 20c:	b8 01 00 00 00       	mov    $0x1,%eax
 211:	e9 e2 00 00 00       	jmp    2f8 <BstInsert+0x139>
 216:	48 83 7d f8 00       	cmpq   $0x0,-0x8(%rbp)
 21b:	75 21                	jne    23e <BstInsert+0x7f>
 21d:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
 221:	48 8b 50 18          	mov    0x18(%rax),%rdx
 225:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
 229:	48 89 d6             	mov    %rdx,%rsi
 22c:	48 89 c7             	mov    %rax,%rdi
 22f:	e8 00 00 00 00       	call   234 <BstInsert+0x75>
 234:	b8 01 00 00 00       	mov    $0x1,%eax
 239:	e9 ba 00 00 00       	jmp    2f8 <BstInsert+0x139>
 23e:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
 242:	48 8b 48 18          	mov    0x18(%rax),%rcx
 246:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
 24a:	48 8b 00             	mov    (%rax),%rax
 24d:	48 8b 55 f0          	mov    -0x10(%rbp),%rdx
 251:	48 89 d6             	mov    %rdx,%rsi
 254:	48 89 c7             	mov    %rax,%rdi
 257:	ff d1                	call   *%rcx
 259:	85 c0                	test   %eax,%eax
 25b:	79 4c                	jns    2a9 <BstInsert+0xea>
 25d:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
 261:	48 8b 40 10          	mov    0x10(%rax),%rax
 265:	48 85 c0             	test   %rax,%rax
 268:	75 26                	jne    290 <BstInsert+0xd1>
 26a:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
 26e:	48 8b 50 18          	mov    0x18(%rax),%rdx
 272:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
 276:	48 89 d6             	mov    %rdx,%rsi
 279:	48 89 c7             	mov    %rax,%rdi
 27c:	e8 00 00 00 00       	call   281 <BstInsert+0xc2>
 281:	48 8b 55 f8          	mov    -0x8(%rbp),%rdx
 285:	48 89 42 10          	mov    %rax,0x10(%rdx)
 289:	b8 01 00 00 00       	mov    $0x1,%eax
 28e:	eb 68                	jmp    2f8 <BstInsert+0x139>
 290:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
 294:	48 8b 40 10          	mov    0x10(%rax),%rax
 298:	48 8b 55 f0          	mov    -0x10(%rbp),%rdx
 29c:	48 89 d6             	mov    %rdx,%rsi
 29f:	48 89 c7             	mov    %rax,%rdi
 2a2:	e8 00 00 00 00       	call   2a7 <BstInsert+0xe8>
 2a7:	eb 4a                	jmp    2f3 <BstInsert+0x134>
 2a9:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
 2ad:	48 8b 40 08          	mov    0x8(%rax),%rax
 2b1:	48 85 c0             	test   %rax,%rax
 2b4:	75 26                	jne    2dc <BstInsert+0x11d>
 2b6:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
 2ba:	48 8b 50 18          	mov    0x18(%rax),%rdx
 2be:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
 2c2:	48 89 d6             	mov    %rdx,%rsi
 2c5:	48 89 c7             	mov    %rax,%rdi
 2c8:	e8 00 00 00 00       	call   2cd <BstInsert+0x10e>
 2cd:	48 8b 55 f8          	mov    -0x8(%rbp),%rdx
 2d1:	48 89 42 08          	mov    %rax,0x8(%rdx)
 2d5:	b8 01 00 00 00       	mov    $0x1,%eax
 2da:	eb 1c                	jmp    2f8 <BstInsert+0x139>
 2dc:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
 2e0:	48 8b 40 08          	mov    0x8(%rax),%rax
 2e4:	48 8b 55 f0          	mov    -0x10(%rbp),%rdx
 2e8:	48 89 d6             	mov    %rdx,%rsi
 2eb:	48 89 c7             	mov    %rax,%rdi
 2ee:	e8 00 00 00 00       	call   2f3 <BstInsert+0x134>
 2f3:	b8 00 00 00 00       	mov    $0x0,%eax
 2f8:	c9                   	leave  
 2f9:	c3                   	ret    

00000000000002fa <BstFind>:
 2fa:	f3 0f 1e fa          	endbr64 
 2fe:	55                   	push   %rbp
 2ff:	48 89 e5             	mov    %rsp,%rbp
 302:	48 83 ec 10          	sub    $0x10,%rsp
 306:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
 30a:	48 89 75 f0          	mov    %rsi,-0x10(%rbp)
 30e:	48 83 7d f8 00       	cmpq   $0x0,-0x8(%rbp)
 313:	75 07                	jne    31c <BstFind+0x22>
 315:	b8 00 00 00 00       	mov    $0x0,%eax
 31a:	eb 79                	jmp    395 <BstFind+0x9b>
 31c:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
 320:	48 8b 48 18          	mov    0x18(%rax),%rcx
 324:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
 328:	48 8b 00             	mov    (%rax),%rax
 32b:	48 8b 55 f0          	mov    -0x10(%rbp),%rdx
 32f:	48 89 d6             	mov    %rdx,%rsi
 332:	48 89 c7             	mov    %rax,%rdi
 335:	ff d1                	call   *%rcx
 337:	85 c0                	test   %eax,%eax
 339:	75 06                	jne    341 <BstFind+0x47>
 33b:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
 33f:	eb 54                	jmp    395 <BstFind+0x9b>
 341:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
 345:	48 8b 40 08          	mov    0x8(%rax),%rax
 349:	48 85 c0             	test   %rax,%rax
 34c:	74 0d                	je     35b <BstFind+0x61>
 34e:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
 352:	48 8b 40 10          	mov    0x10(%rax),%rax
 356:	48 85 c0             	test   %rax,%rax
 359:	75 07                	jne    362 <BstFind+0x68>
 35b:	b8 00 00 00 00       	mov    $0x0,%eax
 360:	eb 33                	jmp    395 <BstFind+0x9b>
 362:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
 366:	48 8b 40 08          	mov    0x8(%rax),%rax
 36a:	48 8b 55 f0          	mov    -0x10(%rbp),%rdx
 36e:	48 89 d6             	mov    %rdx,%rsi
 371:	48 89 c7             	mov    %rax,%rdi
 374:	e8 00 00 00 00       	call   379 <BstFind+0x7f>
 379:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
 37d:	48 8b 40 10          	mov    0x10(%rax),%rax
 381:	48 8b 55 f0          	mov    -0x10(%rbp),%rdx
 385:	48 89 d6             	mov    %rdx,%rsi
 388:	48 89 c7             	mov    %rax,%rdi
 38b:	e8 00 00 00 00       	call   390 <BstFind+0x96>
 390:	b8 00 00 00 00       	mov    $0x0,%eax
 395:	c9                   	leave  
 396:	c3                   	ret    

0000000000000397 <BstForEach>:
 397:	f3 0f 1e fa          	endbr64 
 39b:	55                   	push   %rbp
 39c:	48 89 e5             	mov    %rsp,%rbp
 39f:	48 83 ec 20          	sub    $0x20,%rsp
 3a3:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
 3a7:	48 89 75 f0          	mov    %rsi,-0x10(%rbp)
 3ab:	48 89 55 e8          	mov    %rdx,-0x18(%rbp)
 3af:	48 83 7d f8 00       	cmpq   $0x0,-0x8(%rbp)
 3b4:	75 07                	jne    3bd <BstForEach+0x26>
 3b6:	b8 00 00 00 00       	mov    $0x0,%eax
 3bb:	eb 52                	jmp    40f <BstForEach+0x78>
 3bd:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
 3c1:	48 8b 00             	mov    (%rax),%rax
 3c4:	48 8b 55 e8          	mov    -0x18(%rbp),%rdx
 3c8:	48 8b 4d f0          	mov    -0x10(%rbp),%rcx
 3cc:	48 89 d6             	mov    %rdx,%rsi
 3cf:	48 89 c7             	mov    %rax,%rdi
 3d2:	ff d1                	call   *%rcx
 3d4:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
 3d8:	48 8b 40 08          	mov    0x8(%rax),%rax
 3dc:	48 8b 55 e8          	mov    -0x18(%rbp),%rdx
 3e0:	48 8b 4d f0          	mov    -0x10(%rbp),%rcx
 3e4:	48 89 ce             	mov    %rcx,%rsi
 3e7:	48 89 c7             	mov    %rax,%rdi
 3ea:	e8 00 00 00 00       	call   3ef <BstForEach+0x58>
 3ef:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
 3f3:	48 8b 40 10          	mov    0x10(%rax),%rax
 3f7:	48 8b 55 e8          	mov    -0x18(%rbp),%rdx
 3fb:	48 8b 4d f0          	mov    -0x10(%rbp),%rcx
 3ff:	48 89 ce             	mov    %rcx,%rsi
 402:	48 89 c7             	mov    %rax,%rdi
 405:	e8 00 00 00 00       	call   40a <BstForEach+0x73>
 40a:	b8 01 00 00 00       	mov    $0x1,%eax
 40f:	c9                   	leave  
 410:	c3                   	ret    

0000000000000411 <BstSize>:
 411:	f3 0f 1e fa          	endbr64 
 415:	55                   	push   %rbp
 416:	48 89 e5             	mov    %rsp,%rbp
 419:	53                   	push   %rbx
 41a:	48 83 ec 18          	sub    $0x18,%rsp
 41e:	48 89 7d e8          	mov    %rdi,-0x18(%rbp)
 422:	48 83 7d e8 00       	cmpq   $0x0,-0x18(%rbp)
 427:	75 07                	jne    430 <BstSize+0x1f>
 429:	b8 00 00 00 00       	mov    $0x0,%eax
 42e:	eb 2a                	jmp    45a <BstSize+0x49>
 430:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
 434:	48 8b 40 10          	mov    0x10(%rax),%rax
 438:	48 89 c7             	mov    %rax,%rdi
 43b:	e8 00 00 00 00       	call   440 <BstSize+0x2f>
 440:	48 89 c3             	mov    %rax,%rbx
 443:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
 447:	48 8b 40 08          	mov    0x8(%rax),%rax
 44b:	48 89 c7             	mov    %rax,%rdi
 44e:	e8 00 00 00 00       	call   453 <BstSize+0x42>
 453:	48 01 d8             	add    %rbx,%rax
 456:	48 83 c0 01          	add    $0x1,%rax
 45a:	48 8b 5d f8          	mov    -0x8(%rbp),%rbx
 45e:	c9                   	leave  
 45f:	c3                   	ret    

0000000000000460 <BstIsEmpty>:
 460:	f3 0f 1e fa          	endbr64 
 464:	55                   	push   %rbp
 465:	48 89 e5             	mov    %rsp,%rbp
 468:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
 46c:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
 470:	48 8b 40 08          	mov    0x8(%rax),%rax
 474:	48 85 c0             	test   %rax,%rax
 477:	75 19                	jne    492 <BstIsEmpty+0x32>
 479:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
 47d:	48 8b 40 10          	mov    0x10(%rax),%rax
 481:	48 85 c0             	test   %rax,%rax
 484:	75 0c                	jne    492 <BstIsEmpty+0x32>
 486:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
 48a:	48 8b 00             	mov    (%rax),%rax
 48d:	48 85 c0             	test   %rax,%rax
 490:	74 07                	je     499 <BstIsEmpty+0x39>
 492:	48 83 7d f8 00       	cmpq   $0x0,-0x8(%rbp)
 497:	75 07                	jne    4a0 <BstIsEmpty+0x40>
 499:	b8 01 00 00 00       	mov    $0x1,%eax
 49e:	eb 05                	jmp    4a5 <BstIsEmpty+0x45>
 4a0:	b8 00 00 00 00       	mov    $0x0,%eax
 4a5:	5d                   	pop    %rbp
 4a6:	c3                   	ret    

00000000000004a7 <SwitchValues>:
 4a7:	f3 0f 1e fa          	endbr64 
 4ab:	55                   	push   %rbp
 4ac:	48 89 e5             	mov    %rsp,%rbp
 4af:	48 83 ec 10          	sub    $0x10,%rsp
 4b3:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
 4b7:	89 75 f4             	mov    %esi,-0xc(%rbp)
 4ba:	48 83 7d f8 00       	cmpq   $0x0,-0x8(%rbp)
 4bf:	75 07                	jne    4c8 <SwitchValues+0x21>
 4c1:	b8 00 00 00 00       	mov    $0x0,%eax
 4c6:	eb 71                	jmp    539 <SwitchValues+0x92>
 4c8:	83 7d f4 00          	cmpl   $0x0,-0xc(%rbp)
 4cc:	74 14                	je     4e2 <SwitchValues+0x3b>
 4ce:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
 4d2:	48 8b 40 10          	mov    0x10(%rax),%rax
 4d6:	48 85 c0             	test   %rax,%rax
 4d9:	75 07                	jne    4e2 <SwitchValues+0x3b>
 4db:	b8 00 00 00 00       	mov    $0x0,%eax
 4e0:	eb 57                	jmp    539 <SwitchValues+0x92>
 4e2:	83 7d f4 00          	cmpl   $0x0,-0xc(%rbp)
 4e6:	74 17                	je     4ff <SwitchValues+0x58>
 4e8:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
 4ec:	48 8b 40 10          	mov    0x10(%rax),%rax
 4f0:	8b 55 f4             	mov    -0xc(%rbp),%edx
 4f3:	89 d6                	mov    %edx,%esi
 4f5:	48 89 c7             	mov    %rax,%rdi
 4f8:	e8 00 00 00 00       	call   4fd <SwitchValues+0x56>
 4fd:	eb 36                	jmp    535 <SwitchValues+0x8e>
 4ff:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
 503:	48 8b 40 08          	mov    0x8(%rax),%rax
 507:	48 85 c0             	test   %rax,%rax
 50a:	75 14                	jne    520 <SwitchValues+0x79>
 50c:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
 510:	48 8b 40 10          	mov    0x10(%rax),%rax
 514:	48 85 c0             	test   %rax,%rax
 517:	75 07                	jne    520 <SwitchValues+0x79>
 519:	b8 00 00 00 00       	mov    $0x0,%eax
 51e:	eb 19                	jmp    539 <SwitchValues+0x92>
 520:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
 524:	48 8b 40 08          	mov    0x8(%rax),%rax
 528:	8b 55 f4             	mov    -0xc(%rbp),%edx
 52b:	89 d6                	mov    %edx,%esi
 52d:	48 89 c7             	mov    %rax,%rdi
 530:	e8 00 00 00 00       	call   535 <SwitchValues+0x8e>
 535:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
 539:	c9                   	leave  
 53a:	c3                   	ret    

000000000000053b <NewNode>:
 53b:	f3 0f 1e fa          	endbr64 
 53f:	55                   	push   %rbp
 540:	48 89 e5             	mov    %rsp,%rbp
 543:	48 83 ec 20          	sub    $0x20,%rsp
 547:	48 89 7d e8          	mov    %rdi,-0x18(%rbp)
 54b:	48 89 75 e0          	mov    %rsi,-0x20(%rbp)
 54f:	bf 20 00 00 00       	mov    $0x20,%edi
 554:	e8 00 00 00 00       	call   559 <NewNode+0x1e>
 559:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
 55d:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
 561:	48 8b 55 e8          	mov    -0x18(%rbp),%rdx
 565:	48 89 10             	mov    %rdx,(%rax)
 568:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
 56c:	48 c7 40 08 00 00 00 	movq   $0x0,0x8(%rax)
 573:	00 
 574:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
 578:	48 c7 40 10 00 00 00 	movq   $0x0,0x10(%rax)
 57f:	00 
 580:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
 584:	48 8b 55 e0          	mov    -0x20(%rbp),%rdx
 588:	48 89 50 18          	mov    %rdx,0x18(%rax)
 58c:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
 590:	c9                   	leave  
 591:	c3                   	ret    
