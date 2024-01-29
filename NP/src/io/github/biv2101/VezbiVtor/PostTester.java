package io.github.biv2101.VezbiVtor;

import java.util.*;
import java.util.stream.Collectors;
import java.util.stream.IntStream;

class Comment {
    private String username;
    private String commentId;
    private String content;
    private String replyToId;
    private List<Comment> replies;

    private int likes;
    private int indentationLevel;

    public int getIndentationLevel() {
        return indentationLevel;
    }

    public Comment(String username, String commentId, String content, String replyToId, int level) {
        this.username = username;
        this.commentId = commentId;
        this.content = content;
        this.replyToId = replyToId;
        indentationLevel = level;
        likes = 0;
        replies = new ArrayList<>();
    }

    public int getLikes() {
        return replies.stream().mapToInt(x -> x.getLikes()).sum() + likes;
    }

    public void addReply(Comment c) {
        replies.add(c);
    }

    public String getAllComments() {
        StringBuilder sb = new StringBuilder();
        replies.stream().sorted(Comparator.comparing(Comment::getLikes).reversed()).forEach(sb::append);
        return sb.toString();
    }

    public int getNumReplies()
    {
        return replies.stream().mapToInt(x-> x.getNumReplies()).sum() + replies.size();
    }

    public String getCommentId() {
        return commentId;
    }

    public void like()
    {
        likes++;
    }

    @Override
    public String toString() {
        return String.format("\n%sComment: %s\n%sWritten by: %s\n%sLikes: %d%s", "    ".repeat(indentationLevel), content, "    ".repeat(indentationLevel), username, "    ".repeat(indentationLevel), likes, getAllComments());
    }
}

class Post {
    private String postAuthor;
    private String postContent;

    private List<Comment> comments;

    public Post(String postAuthor, String postContent) {
        this.postAuthor = postAuthor;
        this.postContent = postContent;
        comments = new ArrayList<>();
    }

    public Comment findComment(String id)
    {
        return comments.stream().filter(x->x.getCommentId().equals(id)).findFirst().orElse(null);
    }
    public void addComment(String username, String commentId, String content, String replyToId) {
        Comment toadd = new Comment(username, commentId, content, replyToId, (replyToId == null) ? 2 : findComment(replyToId).getIndentationLevel() + 1);
        if (findComment(replyToId) != null) {
            findComment(replyToId).addReply(toadd);
        }
        comments.add(toadd);
    }

    public String getPostAuthor() {
        return postAuthor;
    }

    public String getPostContent() {
        return postContent;
    }

    public String printComments() {
        StringBuilder sb = new StringBuilder();
        comments.stream().filter(c -> c.getIndentationLevel() == 2).sorted(Comparator.comparing(Comment::getLikes).reversed()).forEach(sb::append);
        return sb.toString();
    }

    public void likeComment (String commentId)
    {
        findComment(commentId).like();
    }

    @Override
    public String toString() {
        return String.format("Post: %s\nWritten by: %s\nComments: %s\n", postContent, postAuthor, printComments());
    }
}


public class PostTester {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        String postAuthor = sc.nextLine();
        String postContent = sc.nextLine();

        Post p = new Post(postAuthor, postContent);

        while (sc.hasNextLine()) {
            String line = sc.nextLine();
            String[] parts = line.split(";");
            String testCase = parts[0];

            if (testCase.equals("addComment")) {
                String author = parts[1];
                String id = parts[2];
                String content = parts[3];
                String replyToId = null;
                if (parts.length == 5) {
                    replyToId = parts[4];
                }
                p.addComment(author, id, content, replyToId);
            } else if (testCase.equals("likes")) { //likes;1;2;3;4;1;1;1;1;1 example
                for (int i = 1; i < parts.length; i++) {
                    p.likeComment(parts[i]);
                }
            } else {
                System.out.println(p);
            }

        }
    }
}
